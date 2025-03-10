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
acb_theta_naive_proj(acb_ptr th, acb_srcptr z, slong nb_z, const acb_mat_t tau,
                     slong prec)
{
    slong g = acb_mat_nrows(tau);
    slong n = 1 << g;
    slong k;

    acb_theta_naive(th, z, nb_z, tau, prec);
    for (k = 0; k < nb_z; k++)
    {
        _acb_vec_scalar_div(&th[k * n + 1], &th[k * n + 1], n - 1, &th[k * n],
                            prec);
        acb_one(&th[k * n]);
    }
}
