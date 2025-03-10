/*
    Copyright (C) 2023 Jean Kieffer

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_theta.h"

void
acb_theta_precomp_init(acb_theta_precomp_t D, slong nb_z, slong g)
{
    acb_mat_init(acb_theta_precomp_exp_mat(D), g, g);
    D->indices = flint_malloc((g + 1) * sizeof(slong));
    D->indices[g] = 0;
    D->exp_z = _acb_vec_init(nb_z * g);
    acb_theta_precomp_nb_z(D) = nb_z;
}
