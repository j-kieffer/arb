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
acb_theta_eld_interval(slong * min, slong * mid, slong * max,
                       const arb_t ctr, const arf_t rad, int a, slong prec)
{
    arb_t x, y;
    arf_t b;

    if (!arb_is_finite(ctr) || !arf_is_finite(rad))
    {
        flint_printf("acb_theta_eld_interval: Error (infinite values)\n");
        arb_printd(ctr, 30);
        flint_printf("\n");
        arf_printd(rad, 30);
        flint_printf("\n");
        fflush(stdout);
        flint_abort();
    }

    arb_init(x);
    arb_init(y);
    arf_init(b);

    arb_sub_si(x, ctr, a, prec);
    arb_mul_2exp_si(x, x, -1);
    *mid = 2 * arf_get_si(arb_midref(x), ARF_RND_NEAR) + a;

    arb_set_arf(y, rad);
    arb_mul_2exp_si(y, y, -1);
    arb_add(y, x, y, prec);
    arb_get_ubound_arf(b, y, prec);
    *max = 2 * arf_get_si(b, ARF_RND_FLOOR) + a;

    arb_set_arf(y, rad);
    arb_mul_2exp_si(y, y, -1);
    arb_sub(y, x, y, prec);
    arb_get_lbound_arf(b, y, prec);
    *min = 2 * arf_get_si(b, ARF_RND_CEIL) + a;

    arb_clear(x);
    arb_clear(y);
    arf_clear(b);
}
