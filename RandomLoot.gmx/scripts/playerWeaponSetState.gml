///playerWeaponSetState(WEAPON_STATES.__)
with (weaponObj)
{
    state = argument[0];
    attackCount = 0; // warning
    animEnded = 0;
    anImageIndex = 0;
    if (oPlayer.weapon == WEAPONS.__NONE)
    {
        sprite_index = -1;
        anImageSpeed = 0;
        exit;
    }
    //SWITCH ADD WEAPON_STATES  
    switch (state)
    {
    case WEAPON_STATES.__MOVE:
        hitCount = 0;
        animIndex = 0;
        anOffXNeed[0] = 0;
        anOffYNeed[0] = 0;
        sprite_index = oPlayer.weaponSprite[0];
        anImageSpeed = oPlayer.weaponAnimSpeed[0];
        with (oPlayer)
            physicalClearMaskKick();
        break;
        
        
        
        
    case WEAPON_STATES.__RANGE_SHOT:
        if (oPlayer.weaponAmmo < oPlayer.weaponInf[W_PR.__BULLETS_PER_SHOT])
        {
            canAttackTmr = -1;
        }
        else
        {
            canAttack = 0;
            canAttackTmr = oPlayer.weaponInf[W_PR.__SHOOT_CD];
        }
        
        sprite_index = oPlayer.weaponSprite[1];
        anImageSpeed = oPlayer.weaponAnimSpeed[1];
        break;
    case WEAPON_STATES.__RANGE_RECOIL:
        sprite_index = oPlayer.weaponSprite[2];
        anImageSpeed = oPlayer.weaponAnimSpeed[2];
        break;
        
    case WEAPON_STATES.__RANGE_RELOAD:
        sprite_index = oPlayer.weaponSprite[0];
        anImageSpeed = oPlayer.weaponAnimSpeed[0];
        break;
        
        
        
        
    case WEAPON_STATES.__MELEE_DOWN:
        canAttack = 0;
        canAttackTmr = oPlayer.weaponInf[W_PR.__ME_SHOOT_CD];

        angleNeed = angleNeedDown[animIndex] * sign(image_xscale); //+ (90 - angleNeedDown) * (image_xscale < 0); //+ 180 * (image_xscale < 0) + angleNeedDown * -1 * (image_xscale < 0);
        angleRot = angleRotDown[animIndex];
        angleBegin = image_angle;
        
        sprite_index = oPlayer.weaponSprite[1];
        anImageSpeed = oPlayer.weaponAnimSpeed[0];
        break;
        
    case WEAPON_STATES.__MELEE_UP:
        angleNeed = angleNeedUp[animIndex];// + 180 * (image_xscale < 0) + angleNeedUp * -1 * (image_xscale < 0);
        angleRot = angleRotUp[animIndex];
        
        sprite_index = oPlayer.weaponSprite[2];
        anImageSpeed = oPlayer.weaponAnimSpeed[2];
        break;
        
    case WEAPON_STATES.__RETURN_TO_TOP:
        angleNeed = angleNeedUp[animIndex];
        angleRot = angleRotUp[animIndex];
        break;
    }
    anImageNumber = sprite_get_number(sprite_index);
}


