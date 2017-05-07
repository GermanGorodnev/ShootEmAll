///colPlaceFree(x_to, y_to, solid only)
if (instance_exists(oLevel))
{
    var xto = argument[0],
        yto = argument[1];
    var xo = x,
        yo = y;
        
    x = xto;
    y = yto;
    var rd = bbox_right div LEVEL.TILE_W,
        ld = bbox_left div LEVEL.TILE_W,
        td = bbox_top div LEVEL.TILE_H,
        bd = bbox_bottom div LEVEL.TILE_H;
    
    var xmeet = (oLevel.level[# rd, td] & argument[2])
        || (oLevel.level[# ld, td] & argument[2]);
        
    var ymeet = (oLevel.level[# rd, bd] & argument[2])
        || (oLevel.level[# ld, bd] & argument[2]);
        
    x = xo;
    y = yo;

    if (xmeet || ymeet)
        return 0;
    return 1;
}
else
{
    var nn = argument[2];
    return !place_meeting(argument[0], argument[1], oSolidObject);
}
