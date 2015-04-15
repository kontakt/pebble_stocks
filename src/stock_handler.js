// Initialization event
Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
    Pebble.sendAppMessage({"status" : 1}); // Ready
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
        getStock("GOOG", 0);
        break;
    }
  }
);

// Retrieves stock data and hands it off to the pebble
function getStock(symbol, index){
  console.log("Getting stock "+symbol);
  // Request from yahoo API
  var requestURL = 
        "https://finance.yahoo.com/webservice/v1/symbols/"+symbol+"/quote?format=json";
	var request = new XMLHttpRequest();
	request.open("GET", requestURL, false);
  request.send();
  
  // Parse the response
  var response = JSON.parse(request.responseText);
  console.log(response.list.resources[0].resource.fields.symbol);
  
  // Send to pebble
  Pebble.sendAppMessage({
    "index" : index,
    "symbol" : response.list.resources[0].resource.fields.symbol,
    "price" : "$"+response.list.resources[0].resource.fields.price}
    );
}