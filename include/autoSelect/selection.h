#pragma once

#include <string>

//selector configuration
#define HUE 154
#define DEFAULT 6
#define AUTONS "Cl.WP", "Cl.Dis", "F.WP", "F.3B", "F.5B", "Non"

namespace selector{

extern int auton;
const char *b[] = {AUTONS, ""};
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}
