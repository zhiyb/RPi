#include "basic.h"
#include "object.h"

class object *gRoot = new object((class object *)-1);
class object *gAxis = new object(gRoot, point(160, 120, -200));
