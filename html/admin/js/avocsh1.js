function AvocadoConnection () {
  
}

function TRI_SYS_OUTPUT (a, b, c, d, e, f, g, h) {
  return true;    
}

var avocado = new AvocadoConnection();

AvocadoConnection.prototype.get = function (url, obj) {
var msg; 
  $.ajax({
    async: false, 
    type: "GET",
    url: url, 
    contentType: "application/json",
    processData: false, 
    success: function(data) {
      msg = data;
    },
    error: function(data) {
      msg = data; 
    }
  });
  return msg;  
}


AvocadoConnection.prototype.delete = function (url, obj) {
var msg; 
  $.ajax({
    async: false, 
    type: "DELETE",
    url: url, 
    contentType: "application/json",
    processData: false, 
    success: function(data) {
      msg = JSON.stringify(data); 
    },
    error: function(data) {
      msg = JSON.stringify(data);  
    }
  });
  return msg;  
}


AvocadoConnection.prototype.post = function (url, obj) {
var msg; 
  $.ajax({
    async: false, 
    type: "POST",
    url: url, 
    data: obj, 
    contentType: "application/json",
    processData: false, 
    success: function(data) {
      msg = JSON.stringify(data); 
    },
    error: function(data) {
      msg = JSON.stringify(data);  
    }
  });
  return msg;  
}


AvocadoConnection.prototype.put = function (url) {
var msg; 
  $.ajax({
    async: false, 
    type: "PUT",
    url: url, 
    data: obj, 
    contentType: "application/json",
    processData: false, 
    success: function(data) {
      msg = JSON.stringify(data); 
    },
    error: function(data) {
      msg = JSON.stringify(data);  
    }
  });
  return msg;  
}
