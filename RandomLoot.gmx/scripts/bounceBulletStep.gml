if (speed > 0)
{
    var _arr = colPlaceFreeSide(x, y, collideWith);
    if (_arr != -1)
    {
        speed = max(0, speed - 0.1);
        // bounce 
        switch (_arr)
        {
        case 0: // right
            var na = 180;
            direction = 2 * na  - 180 - direction;        
            break;
        case 1: // top
            var na = 270;
            direction = 2 * na  - 180 - direction;            
            break;
        case 2: // left
            var na = 0;
            direction = 2 * na  - 180 - direction;            
            break;
        case 3: // bot
            var na = 90;
            direction = 2 * na  - 180 - direction;   
            break;     
        } 
    }
    _arr = 0;
}

