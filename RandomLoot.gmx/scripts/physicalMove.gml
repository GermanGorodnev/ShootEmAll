///physicalMove(collideWith bitmask)
var clw = argument[0];
var mult = 1;
if (hspd != 0 && vspd != 0)
    mult = .8;

if (vspd != 0)
{
    var a = abs(vspd),
        s = sign(vspd),
        pl = s * mult;
    repeat(a) //for (var i = 0; i < a; i++)
    {
        if (colPlaceFree(x, y + s, clw))
            y += pl;
        else 
            break;
    }
}    
if (hspd != 0)
{
    var a = abs(hspd),
        s = sign(hspd),
        pl = s * mult;
    repeat(a)
    {
        if (colPlaceFree(x + s, y, clw))
            x += pl;
        else
            break;
    }
}













