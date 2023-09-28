// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05,      k06, k07, k08, k09, k10, k11, \
    k12, k13, k14, k15, k16, k17,      k18, k19, k20, k21, k22, k23, \
    k24, k25, k26, k27, k28, k29,      k30, k31, k32, k33, k34, k35, \
    k36, k37, k38, k39, k40, k41, k54, k42, k43, k44, k45, k46, k47, \
         k48, k49, k50, k51, k52, k53, k55, k56, k57, k58, k59 \
) { \
    {k00, k02, k04, k06, k08, k10}, \
    {k01, k03, k05, k07, k09, k11}, \
    {k12, k14, k16, k18, k20, k22}, \
    {k13, k15, k17, k19, k21, k23}, \
    {k24, k26, k28, k30, k32, k34}, \
    {k25, k27, k29, k31, k33, k35}, \
    {k36, k38, k40, k42, k44, k46}, \
    {k37, k39, k41, k43, k45, k47}, \
    {k48, k50, k52, k54, k56, k58}, \
    {k49, k51, k53, k55, k57, k59}, \
}
