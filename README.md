# Wetdata Station

A environment monitoring system using Arduino Uno. This repository contains the website parts of the project. It use Arduino Uno, ESP8266, DHT11, YL-83, YL-69, and [ThingSpeak](http://thingspeak.com/).

Presentation slide: https://docs.google.com/presentation/d/1oLDzClDDtn1sEy0xN_FziVGJhvNlmgRZy0jkRk_f_ak/edit?usp=sharing

See also [cit208-wetdata](https://github.com/andraantariksa/cit208-wetdata)

## Preview

[![https://i.imgur.com/Ysl02SR.png](https://i.imgur.com/Ysl02SR.png)](https://i.imgur.com/Ysl02SR.png)

[![Wetdata Hardware](http://img.youtube.com/vi/xk9uo5Gr-_w/0.jpg)](http://www.youtube.com/watch?v=xk9uo5Gr-_w "Wetdata Hardware")

## Circuit Design

[![https://i.imgur.com/LWmP02R.png](https://i.imgur.com/LWmP02R.png)](https://i.imgur.com/LWmP02R.png)

**Yes, I'm aware if this not a real circuit design.**

## Notes on Development

Somewhat ESP8266 with Arduino can't be used to connect a website with HTTPS, that's why [ThinkSpeak](https://thingspeak.com/) are used for this tasks.

## Reference

- https://medium.com/@cgrant/using-the-esp8266-wifi-module-with-arduino-uno-publishing-to-thingspeak-99fc77122e82
- https://www.youtube.com/watch?v=9Kg9idg2np0
