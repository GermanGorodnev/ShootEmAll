///playerAbilityAdd(ABILITIES.__ new)
var pos = abilCount++;
abils[pos] = argument[0];
abilsTmr[pos] = -1;
switch (argument[0])
{
case ABILITIES.__DASH:
    abilsTmrCnt[pos] = room_speed;
    abilsIco[pos] = 0;
    abilsParams[0] = 180; // distance
    abilsParams[1] = spd; // speed
    psysfloor = global.pse;
    abilsParams[2] = part_emitter_create(psysfloor); // main 10 depth
    break;
case ABILITIES.__HEAL:
    abilsTmrCnt[pos] = room_speed;
    abilsIco[pos] = 1;
    abilsParams[0] = 1;
    break;
case ABILITIES.__SPIKES:
    abilsTmrCnt[pos] = room_speed;
    abilsIco[pos] = 2;
    abilsParams[0] = 1;
    abilsParams[1] = part_emitter_create(global.pse);
    break;
}
