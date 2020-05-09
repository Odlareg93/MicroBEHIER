unsigned long signal_len,t1,t2;   //le temps de pression du bouton
int inputPin = 2;                 
int ledPin = 3;                  
int Buzzer = 7;
String code = "";                 //string ou un charactère est gardè
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C3  131

int notes[] = {
  NOTE_A4, NOTE_B4, NOTE_C3
};
//#############################################################################################################

void setup()
{
  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop()
{
  
//Envoie du code morse
NextDotDash:
  while (digitalRead(inputPin) == HIGH) {}
  t1 = millis();                            //temps de pression du bouton
  digitalWrite(ledPin, HIGH);               //LED pendant que le bouton est prèssè
  tone(Buzzer, NOTE_A4);
  while (digitalRead(inputPin) == LOW) {}
  noTone(Buzzer);
  t2 = millis();                            //temps apres avoir relachè
  digitalWrite(ledPin, LOW);                //LED pendant que le bouton est relachè
  signal_len = t2 - t1;                    
  if (signal_len > 50)                    
  {
    code += readio();                       //la fonction qui determine si c'est un point ou un dash
  }
  while ((millis() - t2) < 500)           //if time between button press greater than 0.5sec, skip loop and go to next alphabet
  {     
    if (digitalRead(inputPin) == LOW)
    {
      goto NextDotDash;
    }
  }
  convertor();                          //fonction de dechifrement du code vers des lettres
}

//#############################################################################################################

char readio()
{
  if (signal_len < 600 && signal_len > 50)
  {
    return '.';                        //if button press less than 0.6sec, it is a dot
  }
  else if (signal_len > 600)
  {
    return '-';                        //if button press more than 0.6sec, it is a dash
  }
}

void convertor()
{
  static String letters[] = {".-", //A
                            "-...", //B
                            "-.-.", //C
                            "-..", //D
                            ".", //E
                            "..-.", //F
                            "--.", //G
                            "....", //H
                            "..", //I
                            ".---", //J
                            "-.-", //K
                            ".-..", //L
                            "--", //M
                            "-.", //N
                            "---", //O
                            ".--.", //P
                            "--.-",//Q
                            ".-.", //R
                            "...", //S
                            "-", //T
                            "..-", //U
                            "...-", //V
                            ".--", //W
                            "-..-", //X
                            "-.--", //Y
                            "--..", //Z
                            "E"
                            };
  int i = 0;
  if (code == ".-.-.-")
  {
    Serial.println(".");        //pour break
  }
  else
  {
    while (letters[i] != "E")  //comparaison du code avec la liste
    {
      if (letters[i] == code)
      {
        Serial.println(char('A' + i));
        break;
      }
      i++;
    }
    if (letters[i] == "E")
    {
      Serial.println("");  //si le code ne correspond a aucune lettre
    }
  }
  code = "";                            //reset du code
}
