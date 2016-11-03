#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>



 
const char* ssid = "DST";
const char* password = "dst54321";
 
WiFiServer server(80);


 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(5, OUTPUT); //device 1
  pinMode(4, OUTPUT); //device 2
  pinMode(0, OUTPUT); //device 3
  pinMode(2, OUTPUT); //device 4
  pinMode(14, OUTPUT);//device 5
  pinMode(12, OUTPUT);//device 6
  pinMode(13, OUTPUT);//device 7
  pinMode(15, OUTPUT);//device 8
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);

  IPAddress ip_server(192, 168, 1, 2);
  IPAddress room1(192, 168, 1, 3); 
  IPAddress room2(192, 168, 1, 4);
  IPAddress room3(192, 168, 1, 5);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255 ,255 ,255 , 0);
  
  WiFi.config(ip_server,gateway,subnet);       //config static local IP 
  WiFi.begin(ssid, password);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {

   int log=0;
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
/*  server.on("/", [](){
    if(!server.authenticate(www_username, www_password))
      return server.requestAuthentication();})
 */
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
 
  if (request.indexOf("/light1on") > 0) 
  {
    digitalWrite(5, HIGH);
    log=1;
  }
  if (request.indexOf("/light1off") >0) 
  {
    digitalWrite(5, LOW);
    log=1;
  }
  if (request.indexOf("/light2on") > 0) 
  {
    digitalWrite(4, HIGH);
    log=1;
  }
  if (request.indexOf("/light2off") >0) 
  {
    digitalWrite(4, LOW);
    log=1;
  }
  if (request.indexOf("/light3on") >0)  
  {
    digitalWrite(0, HIGH);
    log=1;
  }
  if (request.indexOf("/light3off") > 0)  
  {
    digitalWrite(0, LOW);
    log=1;
  }
  if (request.indexOf("/light4on") > 0)  
  {
    digitalWrite(2, HIGH);
    log=1;
  }
  if (request.indexOf("/light4off") > 0)
  {
    digitalWrite(2, LOW);
    log=1;
  }
  if (request.indexOf("/light5on") > 0)  
  {
    digitalWrite(14, HIGH);
    log=1;
  }
  if (request.indexOf("/light5off") > 0)
  {
    digitalWrite(14, LOW);
    log=1;
  }
  if (request.indexOf("/light6on") > 0)  
  {
    digitalWrite(12, HIGH);
    log=1;
  }
  if (request.indexOf("/light6off") > 0)
  {
    digitalWrite(12, LOW);
    log=1;
  }
  if (request.indexOf("/light7on") > 0)  
  {
    digitalWrite(13, HIGH);
    log=1;
  }
  if (request.indexOf("/light7off") > 0)
  {
    digitalWrite(13, LOW);
    log=1;
  }
  if (request.indexOf("/light8on") > 0)  
  {
    digitalWrite(15, HIGH);
    log=1;
  }
  if (request.indexOf("/light8off") > 0)
  {
    digitalWrite(15, LOW);
    log=1;
  }
  if (request.indexOf("/logout") > 0)
  {
    digitalWrite(16, LOW);
    log=0;
  }
  if (request.indexOf("/login") > 0)
  {
    digitalWrite(16, HIGH);
    log=1;
  }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  if (log==0){
  client.println("<!DOCTYPE html><html><head>");

client.println("<meta name='viewport' content='width=device-width, initial-scale=0.9, user-scalable=no'>");
client.println("</head>");
client.println("<style>");
client.println("h2{text-align: center;font-family: sans-serif;}"); 
client.println("form {border: 3px solid #f1f1f1;}");

client.println("input[type=text], input[type=password] {");
    client.println("width: 100%;");
    client.println("padding: 12px 20px;");
    client.println("margin: 8px 0;");
    client.println("display: inline-block;");
    client.println("border: 1px solid #ccc;");
    client.println("box-sizing: border-box;}");

client.println("button {background-color: #4CAF50;");
    client.println("color: white;");
    client.println("padding: 14px 20px;");
    client.println("margin: 8px 0;");
    client.println("border: none;");
    client.println("cursor: pointer;");
    client.println("width: 100%;}");


client.println(".imgcontainer {text-align: center; margin: 20px 0 12px 0;}");
client.println("img.avatar {width: 25%; border-radius: 50%;}");
client.println("span.psw {float: right; padding-top: 16px;}");

/* Change styles for span and cancel button on extra small screens */
client.println("@media screen and (max-width: 300px) {");
    client.println("span.psw {");
       client.println("display: block;");
       client.println("float: none;}}");
   
client.println("</style><body>");

client.println("<h2>Login Page</h2>");

 client.println("<div class=\"container\">");
    client.println("<label><b>Username</b></label>");
    client.println("<input id=\"uname\" type=\"text\" placeholder=\"Enter Username\" value=\"\">");

    client.println("<label><b>Password</b></label>");
    client.println("<input id=\"pwrd\" type=\"password\" placeholder=\"Enter Password\" value =\"\">");
        
    client.println("<button class=\"lgin\" onclick=\"logfunc()\">Login</button>");
    
  

client.println("<script>");
  client.println("function logfunc(){");
  client.println("var user= document.getElementById(\"uname\");");
  client.println("var pass= document.getElementById(\"pwrd\");");
    client.println("if(user.value===\"admin\" && pass.value===\"admin\"){");
   client.println("window.open(\"login\", \"_self\");}");
//don't change the self property, it opens the new url in the same tab
   
  client.println("else  {alert(\"WRONG PASSWORD!!!  Try again\")}}");
  
  
client.println("</script>"); 

client.println("</body>");
client.println("</html>");

}
  if (log!=0){
   client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head>");
client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
client.println("<meta name='viewport' content='width=device-width, initial-scale=0.637, user-scalable=no'>");

client.println("<style>body{text-shadow: 2px 0px 3px;");
client.println("font-family: sans-serif;");
client.println("text-align: center;}");

  client.println(".top{background-color: black;");
  client.println("color: white;");
  client.println("font-size: 40px;");               //edit fontsize
  client.println("padding: 12px;");
  client.println("box-shadow: 0px 4px 5px grey;text-shadow: 2px 0px 3px;}");
  

client.println("p{font-size: 25px;}");
client.println("span{padding: 2px;");                //edit padding
  client.println("font-size: 30px;");
  client.println("font-weight: bold;}");
client.println(".on, .off{");
  client.println("padding: 15px 20px;");
  client.println("font-size: 24px;");
  client.println("text-align: center;");
  client.println("color: #fff;");
  client.println("background-color: teal;");
  client.println("border: none;");
  client.println("border-radius: 10px;");
  client.println("box-shadow: 0px 8px 14px 2px #333;}");

client.println(".off{background-color: red;");
  client.println("padding: 15px 13px ;}");
client.println("</style>");
  
client.println("</head>");
client.println("<body>");
  
  client.println("<div class='top'>HOME AUTOMATION</div>");
  client.println("<hr>");
  client.println("<p>PRESS BUTTONS TO TURN DEVICES ON/OFF</p>");
  client.println("<hr>");
  
  client.println("<div>");
  client.println("<span>DEVICE 1</span>");
  client.println("<span id='1'>STATUS:OFF</span>");
  client.println("<br><br>");
  client.println("<a href='/light1on'><button class='on'>ON</button></a>");
  client.println("<a href='/light1off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    client.println("<br><br>");
  
  client.println("<div>");
  client.println("<span>DEVICE 2</span>");
  client.println("<span id='2'>STATUS:OFF</span>");
  client.println("<br><br>");
  client.println("<a href='/light2on'><button class='on'>ON</button></a>");
  client.println("<a href='/light2off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    client.println("<br><br>");
  
  client.println("<div>");
  client.println("<span>DEVICE 3</span>");
  client.println("<span id='3'>STATUS:OFF</span>");
  client.println("<br><br>");
  client.println("<a href='/light3on'><button class='on'>ON</button></a>");
  client.println("<a href='/light3off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    client.println("<br><br>");
  
  client.println("<div>");
  client.println("<span>DEVICE 4</span>");
  client.println("<span id='4'>STATUS:OFF</span>");
  client.println("<br><br>");
  client.println("<a href='/light4on'><button class='on'>ON</button></a>");
  client.println("<a href='/light4off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    client.println("<br><br>");
  
  client.println("<div>");
  client.println("<span>DEVICE 5</span>");
  client.println("<span id='5'>STATUS:OFF</span>");
  client.println("<a href='/light5on'><button class='on'>ON</button></a>");
  client.println("<a href='/light5off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    client.println("<br><br>");

  client.println("<div>");
  client.println("<span>DEVICE 6</span>");
  client.println("<span id='6'>STATUS:OFF</span>");
  client.println("<a href='/light6on'><button class='on'>ON</button></a>");
  client.println("<a href='/light6off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    client.println("<br><br>");

     client.println("<div>");
  client.println("<span>DEVICE 7</span>");
  client.println("<span id='7'>STATUS:OFF</span>");
  client.println("<a href='/light7on'><button class='on'>ON</button></a>");
  client.println("<a href='/light7off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    client.println("<br><br>");

     client.println("<div>");
  client.println("<span>DEVICE 8</span>");
  client.println("<span id='8'>STATUS:OFF</span>");
  client.println("<a href='/light8on'><button class='on'>ON</button></a>");
  client.println("<a href='/light8off'><button class='off'>OFF</button></a>");
  client.println("</div>");
    

    client.println("<br><br>");
    client.println("<div>");
 // client.println("<span>LOGOUT</span>");
  client.println("<a href='/logout'><button class='off'>LOGOUT</button></a>");       ////edit link for login page
  client.println("</div>");
    client.println("<br><br>");
    
  client.println("<hr>");
  
  if(digitalRead(5)){
  client.print("<script>document.getElementById('1').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('1').innerHTML='STATUS:OFF';</script>");
  }

  if(digitalRead(4)){
  client.print("<script>document.getElementById('2').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('2').innerHTML='STATUS:OFF';</script>");
  }
 
  if(digitalRead(0)){
  client.print("<script>document.getElementById('3').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('3').innerHTML='STATUS:OFF';</script>");
  }

  if(digitalRead(2)){
  client.print("<script>document.getElementById('4').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('4').innerHTML='STATUS:OFF';</script>");
  }

  if(digitalRead(14)){
  client.print("<script>document.getElementById('5').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('5').innerHTML='STATUS:OFF';</script>");
  }

  if(digitalRead(12)){
  client.print("<script>document.getElementById('6').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('6').innerHTML='STATUS:OFF';</script>");
  }

   if(digitalRead(13)){
  client.print("<script>document.getElementById('7').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('7').innerHTML='STATUS:OFF';</script>");
  }

  if(digitalRead(15)){
  client.print("<script>document.getElementById('8').innerHTML='STATUS:ON';</script>");
  }
  else {
  client.print("<script>document.getElementById('8').innerHTML='STATUS:OFF';</script>");
  }
client.println("</body>");  
client.println("</html>");
    }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  
  delay(1);
  Serial.println("Ready for Request");
  Serial.println("");
 
}
