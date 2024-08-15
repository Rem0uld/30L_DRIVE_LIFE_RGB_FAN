//
// Created by LiuLingJian on 24-8-12.
//

#ifndef RGBLEDDRIVE_H
#define RGBLEDDRIVE_H

enum Colors {
  RED = 1,
  GREEN,
  BLUE,
  ALL
};

enum State {
  OFF = 0,
  ON
};
void ShowLedColor(int Colors, int State);
#endif //RGBLEDDRIVE_H
