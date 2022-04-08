#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;



int start() {
char inpt[128];
const char *possibilities[] = { 

"hi","hello","how are you?","what's up?",

"can you add integers for me?","sum","add","add numbers",

"hey","what's your name?","who are you?","what are you?",

"are we friends?","do you have feelings?","are you a robot?","are you human?",

"do you have a brain?","who made you?","can you browse the net?", "what are the main colors?",

"what is C++ ?","what is a computer program?","can you speak other languages?","can you understand binary?",

"how do you understand me?", "bye", "manual"
 };
  size_t n2 = sizeof(possibilities)/sizeof(possibilities[0]);

	while(1) {
		gets(inpt);
		
		if(strcmp(inpt, possibilities[0])==0) {
			
			cout << "hello to you too!" <<endl;
			
		  start();
			
		}
		
	else if(strcmp(inpt, possibilities[1])==0) {
		//hello
		cout << "hi there!"<<endl;
		 start();
	}
	
		else if(strcmp(inpt, possibilities[2])==0) {
		//how are you?	
		cout << "Good and you?"<<endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[3])==0) {
		//what's up?
		cout << "Just chillin' , you?'"<<endl;	
		 start();
	}
	
		else if(strcmp(inpt, possibilities[4])==0) {
		// can you add integers for me?	
		cout << "oh boy it is math again! Ok, I'll do my best. Give me two numbers only, I will try to add them. Enter first number then confirm it, then the second and wait.'"<<endl;
		int nmbr1;
		int nmbr2;
		int sum;
	cin >> nmbr1;
		cout << ".. got the first one, give me the second number:" << endl;
		cin >> nmbr2;
		sum = nmbr1+nmbr2;
		cout << "ok, found it! Here you go ---> "<< nmbr1 << "+" << nmbr2 <<" = " << sum << endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[5])==0) {
		// sum
		cout << "oh boy it is math again! Ok, I'll do my best. Give me two numbers only, I will try to add them. Enter first number then confirm it, then the second and wait.'"<<endl;
		int nmbr1;
		int nmbr2;
		int sum;
	cin >> nmbr1;
		cout << ".. got the first one, give me the second number:" << endl;
		cin >> nmbr2;
		sum = nmbr1+nmbr2;
		cout << "ok, found it! Here you go ---> "<< nmbr1 << "+" << nmbr2 <<" = " << sum << endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[6])==0) {
		//add	
		cout << "oh boy it is math again! Ok, I'll do my best. Give me two numbers only, I will try to add them. Enter first number then confirm it, then the second and wait.'"<<endl;
		int nmbr1;
		int nmbr2;
		int sum;
	cin >> nmbr1;
		cout << ".. got the first one, give me the second number:" << endl;
		cin >> nmbr2;
		sum = nmbr1+nmbr2;
		cout << "ok, found it! Here you go ---> "<< nmbr1 << "+" << nmbr2 <<" = " << sum << endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[7])==0) {
		// add numbers
		cout << "oh boy it is math again! Ok, I'll do my best. Give me two numbers only, I will try to add them. Enter first number then confirm it, then the second and wait.'"<<endl;
		int nmbr1;
		int nmbr2;
		int sum;
	cin >> nmbr1;
		cout << ".. got the first one, give me the second number:" << endl;
		cin >> nmbr2;
		sum = nmbr1+nmbr2;
		cout << "ok, found it! Here you go ---> "<< nmbr1 << "+" << nmbr2 <<" = " << sum << endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[8])==0) {
		//  	hey
		cout << "hey!!!"<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[9])==0) {
		//  what's your name?
		cout << "haha I don't have a name!"<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[10])==0) {
		//  who are you	
		cout << "Well, apparently I am a chatbot written in C++ by Yunus Emre Vurgun in the year of 2022."<<endl;
		 start();
	}else if(strcmp(inpt, possibilities[11])==0) {
		//  what are you?
		cout << "a bot? so....."<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[12])==0) {
		//  	are we friends?
		cout << "sure why not!"<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[13])==0) {
		//  do you have feelings?
		cout << "I only cry when I smell onions."<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[14])==0) {
		//  are you a robot?
		cout << "yes"<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[15])==0) {
		//  	are you human?
		cout << "nope"<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[16])==0) {
		//  do you have a brain?
		cout << "no"<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[17])==0) {
		//  	who made you?
		cout << "I made myself. Just kidding, Yunus Emre Vurgun programmed me."<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[18])==0) {
		//  can you browse the net?
		cout << "no"<<endl;
		 start();
	}
	else if(strcmp(inpt, possibilities[19])==0) {
		//  what are the main colors?
		cout << "Good thing I know them! opss what were they? Let me see... Hmmm. Blue, Red and... (takes a look at notebook and comes back).. Well, they are: 11 basic colors: black, white, red, green, yellow, blue, pink, gray, brown, orange and purple. "<<endl;
		 start();
	}
		else if(strcmp(inpt, possibilities[20])==0) {
		// what is C++ ?
		cout << "C++ is a general-purpose programming language created by Bjarne Stroustrup as an extension of the C programming language, or 'C with Classes''. - Wikipedia"<<endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[21])==0) {
		// what is a computer program?
		cout << "In imperative programming, a computer program is a sequence of instructions in a programming language that a computer can execute or interpret. In declarative programming, a computer program is a set of instructions. A computer program in its human-readable form is called source code. -Wikipedia"<<endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[22])==0) {
		// can you speak other languages?
		cout << "un poco espanol mi amigo! No just kidding. Maybe Turkish? Naber dostum! Not really... Only English."<<endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[23])==0) {
		// can you understand binary?
		cout << "01011001 01001111 01010101 00100000 01000110 01001111 01010101 01001110 01000100 00100000 01010100 01001000 01000101 00100000 01010011 01000101 01000011 01010010 01000101 01010100 00100000 01001101 01000101 01010011 01010011 01000001 01000111 01000101 00100000 01001111 01000110 00100000 01011001 01010101 01001110 01010101 01010011 00100000 01000101 01001101 01010010 01000101 00100000 01010110 01010101 01010010 01000111 01010101 01001110....no because I'm not the computer itself. I am just a program. However, the instructions to run me are converted into binary for the computer to read."<<endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[24])==0) {
		// how do you understand me?
		cout << "I don't. LOL'"<<endl;
		 start();
	}
	
	else if(strcmp(inpt, possibilities[25])==0) {
		// bye
		cout << "ok bye!" <<endl;
		break;
 	}
	

		else if(strcmp(inpt, possibilities[26])==0) {

//manual
	 
			
			cout << "Would you like to see the list of things I understand? (y/n)" << endl;
				char inptMain2ndLayerInside[128];

					gets(inptMain2ndLayerInside);
					
                   if(strcmp(inptMain2ndLayerInside, "y")==0) {
                   	
                   	 cout << "here is the list: " <<endl;
                   	 
                   	 for(size_t i = 0; i < n2; i++ ) {
                   	 	
                   	 	cout <<possibilities[i] <<endl;
                   	 	
						}
								 start();
	                           }
	                           
	                           else {
	                           	cout << "ok let's continue then." <<endl;
	                           	start();
							   }
	}
	
		else {
			cout << "Hmm, I'm not that clever. I do not understand what you are asking me or telling me. Type something else:" << endl;
			  start();
			
		}
	}}
   



int main() {
	const char *possibilitiesMain[] = { 

"hi","hello","how are you?","what's up?",
"can you calculate for me?","sum","add","add numbers",
"hey","what's your name?","who are you?","what are you?",
"are we friends?","do you have feelings?","are you a robot?","are you a human?",
"do you have a brain?","who made you?","can you browse the net?", "what are the main colors?",
"what is C++ ?","what is a computer program?","can you speak other languages?","can you understand binary?",
"how do you understand me?","bye"
 };
 
 size_t n = sizeof(possibilitiesMain)/sizeof(possibilitiesMain[0]);
	cout << "Welcome to Yunus Emre Vurgun's C++ Chat Bot console app. Would you like to continue? (y/n)'" << endl;
	char inptMain[128];
	
	while(1){
		gets(inptMain);
		
		if(strcmp(inptMain, "y")==0) {
			
			cout << "Would you like to see the list of things I understand? (y/n)" << endl;
			
					gets(inptMain);
					
                   if(strcmp(inptMain, "y")==0) {
                   	
                   	 cout << "here is the list: " <<endl;
                   	 
                   	 for(size_t i = 0; i < n; i++ ) {
                   	 	
                   	 	cout <<possibilitiesMain[i] <<endl;
                   	 	
						}
						
                   	 cout << "Now you know me better! Let's start a conversation! Tell me something!'" << endl;
                   	 
		    start();
		    
				   }
				   
				   else {
				   	
				   		cout << "all right then! Let's start a conversation! Tell me something!'" << endl;
		    start();
				   }
		

		}
		
		else if(strcmp(inptMain, "n")==0) {
			cout << "ok, see you later then!"<<endl;
break;
		}
		
		else {
			cout << "ok, I didn't recognize that answer but I accept it as 'n', see you later then!"<<endl;
			break;
		}
		
	}
	


	return 0;
}




//Yunus Emre Vurgun 2022
