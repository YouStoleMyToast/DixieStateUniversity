def distance_2D (w1, z1, w2, z2):
    return math.sqrt(math.pow(float(w1) - float(w2), 2) + math.pow(float(z1) - float(z2), 2))
def rect_touching_rect(w1, z1, wol1, zol1, w2, z2, wol2, zol2):
    w2 -= w1
    z2 -= z1
    ww1 = -wol2
    zz1 = -zol2
    return (w2 > ww1 and w2 < wol1 and z2 > zz1 and z2 < zol1)
def rect_touching_rect2(w1, z1, wol1, zol1, w2, z2, wol2, zol2):
    w2 -= w1
    z2 -= z1
    ww1 = -wol2
    zz1 = -zol2
    return (w2 >= ww1 and w2 <= wol1 and z2 >= zz1 and z2 <= zol1)
def positive(n):
    if n < 0: n = -n; return n
def int_randy(range, add):
    return int((random.random() * range) + add)
def randy(range, add):
    return (random.random() * range) + add
def freaky_rect_switcharoo_2D(pw, pz, pwol, pzol, buffy_the_fat):
    buffy_the_fat2 = buffy_the_fat * 2
    if pwol > 0:
     gw = pw; gwol = pwol
    else:
     gw = pwol + pw; gwol = pw - gw
    if pzol > 0:
     gz = pz; gzol = pzol
    else:
     gz = pzol + pz; gzol = pz - gz
    return [gw - buffy_the_fat, gz - buffy_the_fat, gwol + buffy_the_fat2, gzol + buffy_the_fat2]
def points_rotated_by_angle_2D(points_wz, axis_w, axis_z, angle):
    rotated_points_wz = []
    angle = -angle -90
    angle_times_WOW_pi_divided_by_180 = angle * WOW_pi_divided_by_180
    c1 = math.cos(angle_times_WOW_pi_divided_by_180)
    s1 = math.sin(angle_times_WOW_pi_divided_by_180)
    for pointy in points_wz:
     xt = pointy[0] - axis_w
     yt = pointy[1] - axis_z
     rotated_points_wz += [(-xt * s1) + (yt * c1) + axis_w, (-xt * c1) - (yt * s1) + axis_z]
    return rotated_points_wz
def point_rotated_by_angle_2D(point_w, point_z, axis_w, axis_z, angle):
    angle = -angle -90
    angle_times_WOW_pi_divided_by_180 = angle * WOW_pi_divided_by_180
    c1 = math.cos(angle_times_WOW_pi_divided_by_180)
    s1 = math.sin(angle_times_WOW_pi_divided_by_180)
    xt = point_w - axis_w
    yt = point_z - axis_z
    return (-xt * s1) + (yt * c1) + axis_w, (-xt * c1) - (yt * s1) + axis_z
def arc_tangent_2D(point_w, point_z):
    return math.atan2(point_w, point_z) * WOW_180_divided_by_pi + 180
def arc_tangent_2D_2(point_w, point_z):
    return -math.atan2(point_w, point_z) * WOW_180_divided_by_pi + 180
def ball_to_ball_wzkol_bounce(V1, m1, V2, m2, ball1_is_to_the_left):
    if (ball1_is_to_the_left and V1 >= V2) or (not ball1_is_to_the_left and V1 <= V2):
     Rv1 = V1 - V2
     Rv2 = 0 #V2 - V2
     NewV1 = ((m1 - m2) / float(m1 + m2)) * float(Rv1) + V2
     NewV2 = (( 2 * m1) / float(m1 + m2)) * float(Rv1) + V2
     return NewV1, NewV2
    else:
     return V1, V2
def Find_where_ball_stops_on_line_w(ball_w, ball_z, ball_wol, ball_zol, ball_rad, line_w, line_rad):
    did_collide = False
    totally = ball_rad + line_rad
    b1 = line_w + totally
    b2 = line_w - totally
    New_ball_w = ball_w + ball_wol
    New_ball_z = ball_z + ball_zol
    if   ball_w >= b1 and ball_wol < 0 and New_ball_w < b1: New_ball_w = b1; did_collide = True
    elif ball_w <= b2 and ball_wol > 0 and New_ball_w > b2: New_ball_w = b2; did_collide = True
    else:
     if ball_w > b2 and ball_w < b1:
      if   ball_w > line_w and ball_wol < 0:
       New_ball_w = ball_w; New_ball_z = ball_z
       did_collide = True
      elif ball_w < line_w and ball_wol > 0:
       New_ball_w = ball_w; New_ball_z = ball_z
       did_collide = True
     return New_ball_w, New_ball_z, did_collide
    New_ball_z = (float(ball_zol) / float(ball_wol) * float(New_ball_w - ball_w)) + float(ball_z)
    return New_ball_w, New_ball_z, did_collide
def find_where_ball_collides_on_a_wall(
                                       ball_w, ball_z,
                                       ball_wol, ball_zol,
                                       ball_rad,
                                       wall_type,
                                       wall_w1, wall_z1,
                                       wall_w2, wall_z2,
                                       wall_rad):
    toetoadly = ball_rad + wall_rad
    did_collide = False
    New_ball_w = ball_w + ball_wol
    New_ball_z = ball_z + ball_zol
    angle_hit_at = None
    Relate_ball_w = ball_w - wall_w1
    Relate_ball_z = ball_z - wall_z1
    Relate_wall_w2 = wall_w2 - wall_w1
    Relate_wall_z2 = wall_z2 - wall_z1
    arc_tangeriney = arc_tangent_2D(Relate_wall_w2, Relate_wall_z2)
    Rotate_Relate_ball_w, Rotate_Relate_ball_z, Rotate_Relate_wall_w2, Rotate_Relate_wall_z2 = points_rotated_by_angle_2D(((Relate_ball_w, Relate_ball_z), (Relate_wall_w2, Relate_wall_z2)), 0, 0, arc_tangeriney)
    Rotate_ball_wol, Rotate_ball_zol = point_rotated_by_angle_2D(ball_wol, ball_zol, 0, 0, arc_tangeriney)
    Rotate_Relate_ball_collide_w, Rotate_Relate_ball_collide_z, did_hit_weird_line = Find_where_ball_stops_on_line_w(Rotate_Relate_ball_w, Rotate_Relate_ball_z, Rotate_ball_wol, Rotate_ball_zol, ball_rad, 0, wall_rad)
    if Rotate_Relate_ball_w > -toetoadly and Rotate_Relate_ball_w < toetoadly:
     HE_HE_strange_popper_z = Rotate_Relate_ball_z
    else:
     HE_HE_strange_popper_z = Rotate_Relate_ball_collide_z
    Rotate_angle_hit_at = None
    if   HE_HE_strange_popper_z < Rotate_Relate_wall_z2:
       if ball_is_going_towards_point(Rotate_Relate_ball_w, Rotate_Relate_ball_z, Rotate_ball_wol, Rotate_ball_zol, 0, Rotate_Relate_wall_z2):
        p1_touched, p1_collide_w, p1_collide_z, p1_angle_hit_at = find_where_ball_collides_on_another_ball(Rotate_Relate_ball_w, Rotate_Relate_ball_z, Rotate_ball_wol, Rotate_ball_zol, ball_rad, 0, Rotate_Relate_wall_z2, wall_rad)
        if p1_touched:
         Rotate_Relate_ball_collide_w = p1_collide_w
         Rotate_Relate_ball_collide_z = p1_collide_z
         Rotate_angle_hit_at = p1_angle_hit_at
         did_collide = True
    elif HE_HE_strange_popper_z > 0:
       if ball_is_going_towards_point(Rotate_Relate_ball_w, Rotate_Relate_ball_z, Rotate_ball_wol, Rotate_ball_zol, 0, 0):
        p2_touched, p2_collide_w, p2_collide_z, p2_angle_hit_at = find_where_ball_collides_on_another_ball(Rotate_Relate_ball_w, Rotate_Relate_ball_z, Rotate_ball_wol, Rotate_ball_zol, ball_rad, 0, 0, wall_rad)
        if p2_touched:
         Rotate_Relate_ball_collide_w = p2_collide_w
         Rotate_Relate_ball_collide_z = p2_collide_z
         Rotate_angle_hit_at = p2_angle_hit_at
         did_collide = True
    else:
       if did_hit_weird_line:
        did_collide = True
        if Rotate_Relate_ball_collide_w < 0: Rotate_angle_hit_at = 90
        else: Rotate_angle_hit_at = 270
    if did_collide:
     arc_tangeriney_2 = -arc_tangeriney
     angle_hit_at = Rotate_angle_hit_at + arc_tangeriney
     New_ball_w, New_ball_z = point_rotated_by_angle_2D(Rotate_Relate_ball_collide_w, Rotate_Relate_ball_collide_z, 0, 0, arc_tangeriney_2)
     New_ball_w += wall_w1
     New_ball_z += wall_z1
    return did_collide, New_ball_w, New_ball_z, angle_hit_at  #, is_moving_towards
def zol_at_angle(wol, zol, angle):
    rotated_wol, rotated_zol = point_rotated_by_angle_2D(wol, zol, 0, 0, angle)
    return rotated_zol
def wzol_bounce_at_angle(wol, zol, angle, multi):
    rotated_wol, rotated_zol = point_rotated_by_angle_2D(wol, zol, 0, 0, angle)
    if rotated_zol > 0: rotated_zol = -rotated_zol * multi
    return point_rotated_by_angle_2D(rotated_wol, rotated_zol, 0, 0, -angle)
def ball_is_going_towards_point(ball_w, ball_z, ball_wol, ball_zol, point_w, point_z):
    angley = arc_tangent_2D(ball_w - point_w, ball_z - point_z)
    rotated_wol, rotated_zol = point_rotated_by_angle_2D(ball_wol, ball_zol, 0, 0, angley)
    return rotated_zol > 0
def find_where_ball_collides_on_another_ball (
                                               ball1_w, ball1_z,
                                               ball1_wol, ball1_zol,
                                               ball1_rad,
                                               ball2_w, ball2_z,
                                               ball2_rad
                                             ):
    totally = ball1_rad + ball2_rad
    dis_from_each_other = math.sqrt(math.pow(float(ball1_w) - float(ball2_w), 2) + math.pow(float(ball1_z) - float(ball2_z), 2))
    if dis_from_each_other < totally:
     angley = arc_tangent_2D(ball1_w - ball2_w, ball1_z - ball2_z)
     return True, ball1_w, ball1_z, angley
    else:
        they_did_touch = False
        New_ball1_w = ball1_w + ball1_wol
        New_ball1_z = ball1_z + ball1_zol
        angle_hit_at = None
        Relate_ball1_w = ball1_w - ball2_w
        Relate_ball1_z = ball1_z - ball2_z
        Relate_ball2_w = 0
        Relate_ball2_z = 0
        arcy_tangeriney = arc_tangent_2D(ball1_wol, ball1_zol)
        Rotated_Relate_ball1_w, Rotated_Relate_ball1_z, Rotated_ball1_wol, Rotated_ball1_zol = points_rotated_by_angle_2D(((Relate_ball1_w, Relate_ball1_z), (ball1_wol, ball1_zol)), 0, 0, arcy_tangeriney)
        did_collidey = False
        if Rotated_Relate_ball1_z > 0 and (Rotated_Relate_ball1_w > -totally and Rotated_Relate_ball1_w < totally):
         Rotated_Relate_ball1_collide_w = Rotated_Relate_ball1_w # + Rotated_ball1_wol
         HE_HE = math.pow(Rotated_Relate_ball1_w, 2) - math.pow(totally, 2)
         if HE_HE < 0: HE_HE = -HE_HE
         Rotated_Relate_ball1_collide_z = math.sqrt(HE_HE)
         Rotated_Relate_ball1_z__PLUS__Rotated_ball1_zol = Rotated_Relate_ball1_z + Rotated_ball1_zol
         if Rotated_Relate_ball1_collide_z < Rotated_Relate_ball1_z__PLUS__Rotated_ball1_zol:
          collision_wol = Rotated_ball1_wol
          collision_zol = Rotated_ball1_zol
          Rotated_Relate_ball1_collide_z = Rotated_Relate_ball1_z__PLUS__Rotated_ball1_zol
          angley_to_hit = None
         else:
          did_collidey = True
          they_did_touch = True
          angley_to_hit = arc_tangent_2D(Rotated_Relate_ball1_collide_w, Rotated_Relate_ball1_collide_z)
        else:
         angley_to_hit = None
         collision_wol = Rotated_ball1_wol
         collision_zol = Rotated_ball1_zol
         Rotated_Relate_ball1_collide_w = Rotated_Relate_ball1_w + Rotated_ball1_wol
         Rotated_Relate_ball1_collide_z = Rotated_Relate_ball1_z + Rotated_ball1_zol
        if did_collidey:
         arcy_tangeriney_2 = -arcy_tangeriney
         angle_hit_at = angley_to_hit + arcy_tangeriney
         New_ball1_w, New_ball1_z = point_rotated_by_angle_2D(Rotated_Relate_ball1_collide_w, Rotated_Relate_ball1_collide_z, 0, 0, arcy_tangeriney_2)
         New_ball1_w += ball2_w
         New_ball1_z += ball2_z
    return they_did_touch, New_ball1_w, New_ball1_z, angle_hit_at  #, New_ball1_wol, New_ball1_zol
