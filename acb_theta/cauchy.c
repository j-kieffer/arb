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
acb_theta_cauchy(arf_t bound_der, const arf_t rad, const arf_t bound,
                 slong ord, slong dim, slong prec)
{
    fmpz_t fac, bin;
    arb_t r, m;

    fmpz_init(fac);
    fmpz_init(bin);
    arb_init(r);
    arb_init(m);

    arb_set_arf(r, rad);
    arb_set_arf(m, bound);

    fmpz_bin_uiui(bin, ord + dim, dim);
    fmpz_fac_ui(fac, ord);
    fmpz_mul(fac, fac, bin);
    fmpz_mul_2exp(fac, fac, ord);

    arb_pow_ui(r, r, ord, prec);
    arb_div(r, m, r, prec);
    arb_mul_fmpz(r, r, fac, prec);
    arb_get_ubound_arf(bound_der, r, prec);

    fmpz_clear(fac);
    fmpz_clear(bin);
    arb_clear(r);
    arb_clear(m);
}
