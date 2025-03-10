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
arb_mat_pos_radius(arf_t rad, const arb_mat_t mat, slong prec)
{
    slong g = acb_mat_nrows(mat);
    arb_t abs, lambda, max;
    arf_t r;
    fmpz_t e;
    arb_mat_t test;
    slong j, k;
    int valid;

    arb_init(abs);
    arb_init(lambda);
    arb_init(max);
    arf_init(r);
    fmpz_init(e);
    arb_mat_init(test, g, g);

    arb_mat_pos_lambda(lambda, mat, prec);
    arb_zero(max);
    for (j = 0; j < g; j++)
    {
        for (k = 0; k < g; k++)
        {
            arb_abs(abs, arb_mat_entry(mat, j, k));
            arb_max(max, max, abs, prec);
        }
    }

    /* Take a guess at r */
    arb_mul_si(abs, max, g, prec);
    arb_pow_ui(abs, abs, g, prec);
    arb_div(abs, lambda, abs, prec);
    arb_get_lbound_arf(r, abs, prec);
    arf_frexp(r, e, r);
    arf_one(r);
    arf_mul_2exp_fmpz(r, r, e);

    /* Is r ok? */
    arb_mat_set(test, mat);
    arb_mat_add_error_arf(test, r);
    arb_mat_pos_lambda(lambda, test, prec);
    valid = arb_is_positive(lambda);

    if (!valid)
    {
        /* Reduce r until valid, or we reach prec */
        while (!valid && fmpz_cmp_si(e, -prec) > 0)
        {
            arf_mul_2exp_si(r, r, -1);
            fmpz_add_si(e, e, -1);
            arb_mat_set(test, mat);
            arb_mat_add_error_arf(test, r);
            arb_mat_pos_lambda(lambda, test, prec);
            valid = arb_is_positive(lambda);
        }
    }
    else
    {
        /* Increase r until invalid */
        while (valid)
        {
            arf_mul_2exp_si(r, r, 1);
            fmpz_add_si(e, e, 1);
            arb_mat_set(test, mat);
            arb_mat_add_error_arf(test, r);
            arb_mat_pos_lambda(lambda, test, prec);
            valid = arb_is_positive(lambda);
        }
        arf_mul_2exp_si(r, r, -1);
        fmpz_add_si(e, e, -1);
        valid = 1;
    }

    if (!valid)
        arf_zero(rad);
    else
        arf_set(rad, r);

    arb_clear(abs);
    arb_clear(lambda);
    arb_clear(max);
    arf_clear(r);
    fmpz_clear(e);
    arb_mat_clear(test);
}
