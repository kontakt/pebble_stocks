var stocks = ["GOOG", "APPL", "YHOO", "MSFT"];

// Stock class
function stock(a, b, c, d){
  this.index     = a;
  this.symbol    = b;
  this.price     = c;
  this.change    = d;
}

var data = [];

// Initialization event
Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
    Pebble.sendAppMessage({"status" : 1}); // Ready
    refreshAll();
  }
);

// Message recieve handler
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('Received message: ' + JSON.stringify(e.payload));
    switch(e.payload.command){
      case 0:
        console.log("Test Passed");
        break;
      case 1:
        refreshAll();
        break;
      case 2:
        getStock(stocks[e.payload.detail], e.payload.detail);
        break;
    }
  }
);

// Returns an object containing stock info
function yahooAPIcall(){
  console.log("Getting stocks");
  // Create URL
  var URLprefix = "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20yahoo.finance.quotes%20where%20symbol%20in%20(";
  var URLsuffix = ")&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
  var URLcenter = "";
  for(var i=0; i<stocks.length; i++){
    URLcenter += '"' + stocks[i] + '"';
    if(i == (stocks.length-1))
      break;
    URLcenter += ',';
  }
  
  // Request from yahoo API
  var requestURL = URLprefix + URLcenter + URLsuffix;
  console.log(requestURL);
	var request = new XMLHttpRequest();
	request.open("GET", requestURL, false);
  request.send();
  
  // Parse the response
  var response = JSON.parse(request.responseText);
  return response;
}

// Refreshes all stocks
function refreshAll(){
  for(var i=0; i<stocks.length; i++){
    var stock_data = yahooAPIcall(stocks[i]);
    data[i] = new stock(i,
                        stocks[i],
                        stock_data.query.results.quote[i].Ask,
                        stock_data.query.results.quote[i].change
                       );
  }
}

// Retrieves stock data and hands it off to the pebble
function getStock(symbol, index){
  // Send to pebble
  Pebble.sendAppMessage({
    "index" : index,
    "symbol" : data[index].symbol,
    "price" : "$"+data[index].price}
    );
}