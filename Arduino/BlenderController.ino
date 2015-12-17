#include <Servo.h>

Servo s1, s2;

void setup(){
	Serial.begin(115200);
	Serial.flush();
	s1.attach(9);
	s2.attach(8);
}

String readString(){
	String inString ="";
	char inChar;
	while(Serial.available()>0){
		inChar =(char) Serial.read();
		inString+=inChar;
		delay(1);
	}
	return inString;
}

int* parseString(String msg){
		static int a[2];
		int commaIndex = msg.indexOf(',');
		a[0] = msg.substring(0, commaIndex).toInt();
		a[1] = msg.substring(commaIndex+1).toInt();
		return a;
}



void writeValues(int b[]){
	if(b[0]<20)b[0]=20;
	if(b[0]>150)b[0]=150;
	if(b[1]<40)b[1]=40;
	if(b[1]>160)b[1]=160;

	//s1.write(b[0]);
	s1.write(map(b[0],0,180,150,20));
	s2.write(map(b[1],0,180,40,160));
	Serial.print(b[0]);
	Serial.print("	");
	Serial.println(b[1]);
}


void loop(){
	//Serial.print("a");
    if(Serial.available()){
        String incoming=readString();
        int *angles=parseString(incoming);
        writeValues(angles);
    }
}