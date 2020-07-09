#pragma once

#include "CfgManager.h"

cfg::Config config ("Config.cfg");

//-=Window settings=-

const size_t wWidth  = config.getNumSetting ("wWidth");
const size_t wHeight = config.getNumSetting ("wHeight");

const char * wTitle = "Flappy Man";

      size_t wFpsLimit = config.getNumSetting ("wFpsLimit");

const sf::Color Background (40, 40, 40);

//-=Game settings=-

const size_t HoleMinHeight      = config.getNumSetting ("HoleMinHeight");
const size_t HoleMaxHeight      = config.getNumSetting ("HoleMaxHeight");

const size_t WallMinWidth       = config.getNumSetting ("WallMinWidth");
const size_t WallMaxWidth       = config.getNumSetting ("WallMaxWidth");

const size_t HoleRange          = config.getNumSetting ("HoleRange");

const size_t WallsCount         = config.getNumSetting ("WallsCount");

const double WallsSpeed         = config.getNumSetting ("WallsSpeed");

const double MaxPlayerSpeed     = config.getNumSetting ("MaxPlayerSpeed");

const double PlayerFallVelocity = config.getNumSetting ("PlayerFallVelocity");

const double PlayerJumpVelocity = config.getNumSetting ("PlayerJumpVelocity");

const sf::Color WallColor      (41, 141, 255);
const sf::Color WallBackground (40, 54, 62);
const sf::Color PlayerColor (sf::Color::Red);

//-=Object manager settings=-

const size_t MaxObjects = 100;