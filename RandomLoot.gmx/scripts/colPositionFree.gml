///colPositionFree(x_to, y_to, bitmask)
var xto = median(0, argument[0] div LEVEL.TILE_W, oLevel.ww-1);
    yto = median(0, argument[1] div LEVEL.TILE_H, oLevel.hh-1);
if (oLevel.level[# xto, yto] & argument[2])
    return 0;
return 1;

