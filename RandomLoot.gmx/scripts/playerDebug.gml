if (!global.debug)
    exit;
draw_text(bbox_right, bbox_top - 20, string("cannot shoot: " + string(weaponObj.canAttackTmr)));
switch (weaponObj.state)
{
case WEAPON_STATES.__MELEE_UP:
    draw_text(bbox_right, bbox_top - 5, string("weaponstate: melee up"));
    break;
case WEAPON_STATES.__MELEE_DOWN:
    draw_text(bbox_right, bbox_top - 5, string("weaponstate: melee down"));
    break;
case WEAPON_STATES.__MOVE:
    draw_text(bbox_right, bbox_top - 5, string("weaponstate: move"));
    break;
}

