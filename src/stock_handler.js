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
  console.log(response);
  Pebble.sendAppMessage({
          "symbol":response.list.resources[0].resource.symbol}
        );
  console.log(request.responseText);
}