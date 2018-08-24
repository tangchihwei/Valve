import processing.serial.*; 
 
Serial myPort;    // The serial port
PFont myFont;     // The display font
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 
int portNum = 21;
Table table;
String filename = "test_tof_gen2_";
boolean newSerial = false;
int lengthToToss = 10;
int i = 0;
int startTime = 0;

 
void setup() { 
  size(600,600); 
  printArray(Serial.list()); 

  myPort = new Serial(this, Serial.list()[portNum], 9600); 
  myPort.bufferUntil(lf); 
  myPort.clear();
  
  table = new Table();
  table.addColumn("Time");
  table.addColumn("Sen1");
  table.addColumn("Sen2");
  table.addColumn("Sen3");

  startTime = millis();
} 
 
void draw() { 
  if (newSerial){
    TableRow newRow;
    background(0); 
    textSize(60);  
    //String time = hour() + " : " + minute() + " : " + second();
    int time = (millis()-startTime)/1000;
    int hr = time/3600;
    int min = time/60;
    int sec = time%60;
    newSerial = false;
    textSize(30);
    text("Time since start: " + str(hr) + " : " + str(min) + " : "+ str(sec), 10, 250);
    String[] list = split(inString, ',');
    newRow = table.addRow();
    print(inString);
    textSize(60);
    newRow.setString("Sen1", list[0].substring(5));
    newRow.setString("Sen2", list[1].substring(5));
    newRow.setString("Sen3", list[2].substring(5));
    newRow.setString("Time", str(hr) + " : " + str(min) + " : "+ str(sec));
    text("Sen 1: " + list[0].substring(5), 10, 50); 
    text("Sen 2: " + list[1].substring(5), 10, 150);
    text("Sen 3: " + list[2].substring(5), 10, 300);

  }
} 
 
void serialEvent(Serial p) { 
  inString = p.readString(); 
  if (i < lengthToToss){
    i++;
    p.clear();
  }
  else{
    newSerial = true;
  }
} 

void keyPressed()
{
  //variables used for the filename timestamp
  filename = filename + month() + "_" + day() + "_" + hour() + "_" + minute() + "_" + second()+ ".csv";
  saveTable(table, filename);
  exit();
}
