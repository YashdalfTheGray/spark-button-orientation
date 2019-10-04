// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>

#include "math.h"

int ledPos = 0;
int lightsOn = 0;
int brightness = 10;
int r = 0;
int g = 255;
int b = 0;

InternetButton sb = InternetButton();

void setup()
{
  sb.begin(1);
  sb.setBrightness(brightness);

  Particle.variable("ledPos", ledPos);
  Particle.variable("lightsOn", lightsOn);
  Particle.variable("brightness", brightness);
  Particle.function("toggleLights", toggleLights);
  Particle.function("setBrightness", setBrightness);
}

void loop()
{
  if (lightsOn)
  {
    for (int i = 0; i < 256; i++)
    {
      rainbow(i, 5);
      sb.ledOn(1, r, g, b);
    }
  }
  else
  {
    sb.allLedsOff();
  }
}

int toggleLights(String command)
{
  lightsOn = !lightsOn;
}

int setBrightness(String command)
{
  char inputStr[10];
  command.toCharArray(inputStr, 10);
  int i = atoi(inputStr);

  if (i > 100)
  {
    brightness = 100;
  }
  else if (i < 10)
  {
    brightness = 10;
  }
  else
  {
    brightness = i;
  }

  sb.setBrightness(i);
}

void rainbow(uint8_t wheelPos, uint8_t wait)
{
  if (wheelPos < 85)
  {
    r = wheelPos * 3;
    g = 255 - wheelPos * 3;
    b = 0;
  }
  else if (wheelPos < 170)
  {
    wheelPos -= 85;
    r = 255 - wheelPos * 3;
    g = 0;
    b = wheelPos * 3;
  }
  else
  {
    wheelPos -= 170;
    r = 0;
    g = wheelPos * 3;
    b = 255 - wheelPos * 3;
  }

  delay(wait);
}
