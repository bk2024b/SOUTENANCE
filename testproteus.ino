// ======================================================
// TEST GUIDAGE ROBOT
// VERSION L298N - PROTEUS
// ======================================================

//
// MOTEUR PROPULSION
//

int ENA = 5;
int IN1 = 6;
int IN2 = 4;

//
// MOTEUR GUIDAGE
//

int ENB = 10;
int IN3 = 11;
int IN4 = 12;

//
// CAPTEURS
//

int infra_gauche = 7;
int infra_droite = 8;

//
// BOUTON START/STOP
//

int bouton = 2;

bool robot_actif = true;

bool ancien_etat_bouton = LOW;

// ======================================================
// SETUP
// ======================================================

void setup()
{
    Serial.begin(9600);

    //
    // CAPTEURS
    //

    pinMode(infra_gauche, INPUT);
    pinMode(infra_droite, INPUT);

    //
    // BOUTON
    //

    pinMode(bouton, INPUT);

    //
    // PROPULSION
    //

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    //
    // GUIDAGE
    //

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    Serial.println("SYSTEME GUIDAGE L298N DEMARRE");
}

// ======================================================
// AVANCER
// ======================================================

void avancer()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    analogWrite(ENA, 200);
}

// ======================================================
// TOURNER A DROITE
// ======================================================

void tourner_droite()
{
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(ENB, 120);

    Serial.println("CORRECTION DROITE");
}

// ======================================================
// TOURNER A GAUCHE
// ======================================================

void tourner_gauche()
{
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    analogWrite(ENB, 120);

    Serial.println("CORRECTION GAUCHE");
}

// ======================================================
// STOP GUIDAGE
// ======================================================

void stop_guidage()
{
    analogWrite(ENB, 0);

    Serial.println("GUIDAGE STABLE");
}

// ======================================================
// STOP ROBOT
// ======================================================

void stop_robot()
{
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);

    Serial.println("ROBOT ARRETE");
}

// ======================================================
// GUIDAGE
// ======================================================

void guider()
{
    //
    // SORTIE GAUCHE
    //

    if(digitalRead(infra_gauche) &&
      !digitalRead(infra_droite))
    {
        tourner_droite();
    }

    //
    // SORTIE DROITE
    //

    else if(digitalRead(infra_droite) &&
           !digitalRead(infra_gauche))
    {
        tourner_gauche();
    }

    //
    // ROBOT CENTRE
    //

    else
    {
        stop_guidage();
    }
}

// ======================================================
// LOOP
// ======================================================

void loop()
{
    //
    // LECTURE BOUTON
    //

    bool etat_bouton = digitalRead(bouton);

    //
    // DETECTION IMPULSION
    //

    if(etat_bouton == HIGH &&
       ancien_etat_bouton == LOW)
    {
        robot_actif = !robot_actif;

        delay(200);

        if(robot_actif)
        {
            Serial.println("ROBOT DEMARRE");
        }
        else
        {
            Serial.println("ROBOT STOPPE");
        }
    }

    ancien_etat_bouton = etat_bouton;

    //
    // ROBOT ACTIF
    //

    if(robot_actif)
    {
        avancer();

        guider();
    }

    //
    // ROBOT STOPPE
    //

    else
    {
        stop_robot();
    }

    delay(50);
}