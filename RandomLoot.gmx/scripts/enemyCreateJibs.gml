switch (enemyType)
{
case ENEMY.__PILLOW:
    psys = global.pse;
    pem = part_emitter_create(psys);
    part_emitter_region(psys, pem, x - 5, x + 5, bbox_top + 5, y, ps_shape_rectangle, ps_distr_invgaussian);
    part_emitter_burst(psys, pem, global.pillowjibs, irandom_range(4, 7));
    break;
}
