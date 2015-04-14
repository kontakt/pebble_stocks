// Initialization event
Pebble.addEventListener('ready',
  function(e) {
    console.log('JavaScript app ready and running!');
    getStock("GOOG");
  }
);

function getStock(symbol){
  var requestURL = 
        "https://finance.yahoo.com/webservice/v1/symbols/"+symbol+"/quote?format=json";
	var request = new XMLHttpRequest();
	request.open("GET", requestURL, false);
  request.send(null);
  var response = JSON.parse(request.responseText);
  console.log(response.list.resources[0].resource.fields.symbol);
  Pebble.sendAppMessage({
    "index":0,
    "symbol":response.list.resources[0].resource.fields.symbol,
    "price":"$123.34 -0.34%"}
    );
}