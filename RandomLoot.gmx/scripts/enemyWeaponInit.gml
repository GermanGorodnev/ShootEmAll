///enemyWeaponInit(ENEMY_WEAPON.__)
//SWITCH ADD
switch (argument[0])
{
case ENEMY_WEAPON.__SELF:

    break;
    
case ENEMY_WEAPON.__MACHINEGUN:
    weaponSprite[0] = sEnemyMachinegun;
    weaponSprite[1] = sEnemyMachinegunShoot;
    weaponXoff = 4;
    weaponYoff = -16;
    weaponAnimSpeed[1] = 0.3;
    weaponObj.anMaxAngle = 4;
    ldirx = 37;
    ldiry = 37;
    ldirdir = 12;
    critchance = 0;
    mindmg = 1;
    maxdmg = 1;
    projectileSpeed = 7;
    sprayAngle = 5;
    shootcd = 2 * room_speed;
    break;
    
case ENEMY_WEAPON.__TAZER:
    weaponSprite[0] = sOctoGuardTazer;
    weaponSprite[1] = sOctoGuardTazer;
    weaponXoff = 4;
    weaponYoff = -25;
    weaponAnimSpeed[1] = 0.3;
    weaponObj.anMaxAngle = 4;
    ldirx = 37;
    ldiry = 37;
    ldirdir = 12;
    critchance = 0;
    mindmg = 1;
    maxdmg = 2;
    projectileSpeed = 7;
    sprayAngle = 5;
    shootcd = 2 * room_speed;
    break;
}
enemyWeaponSetState(WEAPON_STATES.__MOVE);
