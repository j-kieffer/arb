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
acb_theta_transform_sqr_proj(acb_ptr res, acb_srcptr th2, const fmpz_mat_t mat,
                             slong prec)
{
    acb_ptr aux;
    slong g = fmpz_mat_nrows(mat) / 2;
    ulong n = 1 << g;
    ulong ab;
    ulong image_ab;
    fmpz_t eps;
    acb_t c;

    aux = _acb_vec_init(n);
    fmpz_init(eps);
    acb_init(c);

    for (ab = 0; ab < n; ab++)
    {
        image_ab = acb_theta_transform_image_char(eps, ab, mat);
        acb_unit_root(c, 4, prec);
        acb_pow_fmpz(c, c, eps, prec);
        acb_mul(c, c, &th2[image_ab], prec);
        acb_set(&aux[ab], c);
    }

    _acb_vec_set(res, aux, n);

    _acb_vec_clear(aux, n);
    fmpz_clear(eps);
    acb_clear(c);
}
