import processing.serial.*;
import oscP5.*;
import netP5.*;

OscP5 oscP5;
Serial p;
int value;
NetAddress destination; 

void setup() {
  size(100, 100);
  
  // need a better way to know this in advance or a way to search
  //println(Serial.list());
  
  //
  String portName = Serial.list()[Serial.list().length - 1];
  p = new Serial(this, portName, 9600);
  
  //
  oscP5 = new OscP5(this, 12000);
  destination = new NetAddress("127.0.0.1", 9010);
}

void draw() {
  if (p.available() > 0) {
    value = p.read();
  }
  
  //
  background(value);
  fill(255 - value);
  text("" + value, 50, 50);
  
  //
  OscMessage m = new OscMessage("/proximity");
  m.add(value);
  oscP5.send(m, destination);
}
