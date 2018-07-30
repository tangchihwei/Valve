import processing.serial.*; 
 
Serial myPort;    // The serial port
PFont myFont;     // The display font
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 
int portNum = 19;
Table table;
String filename = "test_tof_gen2_";

 
void setup() { 
  size(400,200); 
  // You'll need to make this font with the Create Font Tool 
  //myFont = loadFont("ArialMS-18.vlw"); 
  //textFont(myFont, 18); 
  // List all the available serial ports: 
  printArray(Serial.list()); 
  // I know that the first port in the serial list on my mac 
  // is always my  Keyspan adaptor, so I open Serial.list()[0]. 
  // Open whatever port is the one you're using. 
  myPort = new Serial(this, Serial.list()[portNum], 9600); 
  myPort.bufferUntil(lf); 
  
  table = new Table();
  table.addColumn("Time");
  table.addColumn("Gen1");
  table.addColumn("Gen2");
  //table.addColumn("Date");
  
  //TableRow newRow = table.addRow();
  //newRow.setString("Data", "2");
  //String time = hour() + " : " + minute() + " : " + second();
  //newRow.setString("Time", time);
  //newRow.setString("Date", "haha");
  //saveTable(table,filename);
  
} 
 
void draw() { 
  TableRow newRow;
  background(0); 
  textSize(40);
  //text("received: " + inString, 10,50); 
  if(inString.charAt(3) == '1'){
    text("Gen 1: " + inString.substring(5), 10, 50); 
    newRow = table.addRow();
    newRow.setString("Gen1", inString.substring(5));
    String time = hour() + " : " + minute() + " : " + second();
    newRow.setString("Time", time);
  }
  else if(inString.charAt(3) == '2'){
    text("Gen 2: " + inString.substring(5), 10, 120); 
    newRow = table.addRow();
    newRow.setString("Gen2", inString.substring(5));
    String time = hour() + " : " + minute() + " : " + second();
    newRow.setString("Time", time);
  }  
} 
 
void serialEvent(Serial p) { 
  inString = p.readString(); 
} 

void keyPressed()
{
  //variables used for the filename timestamp
  filename = filename + month() + "_" + day() + "_" + hour() + "_" + minute() + "_" + second()+ ".csv";
  saveTable(table, filename);
  exit();
}
