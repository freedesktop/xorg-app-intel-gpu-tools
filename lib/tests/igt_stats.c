/*
 * Copyright © 2015 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include "igt_core.h"
#include "igt_stats.h"

static void test_mean(void)
{
	igt_stats_t stats;
	double mean;

	igt_stats_init(&stats, 5);

	igt_stats_push(&stats, 2);
	igt_stats_push(&stats, 4);
	igt_stats_push(&stats, 6);
	igt_stats_push(&stats, 8);
	igt_stats_push(&stats, 10);

	mean = igt_stats_get_mean(&stats);

	igt_assert(mean == (2 + 4 + 6 + 8 + 10) / 5.);

	igt_stats_fini(&stats);
}

static void test_invalidate_mean(void)
{
	igt_stats_t stats;
	double mean1, mean2;

	igt_stats_init(&stats, 6);

	igt_stats_push(&stats, 2);
	igt_stats_push(&stats, 4);
	igt_stats_push(&stats, 6);
	igt_stats_push(&stats, 8);
	igt_stats_push(&stats, 10);

	mean1 = igt_stats_get_mean(&stats);
	igt_assert(mean1 == (2 + 4 + 6 + 8 + 10) / 5.);

	igt_stats_push(&stats, 100);

	mean2 = igt_stats_get_mean(&stats);
	igt_assert(mean1 != mean2);

	igt_stats_fini(&stats);
}

/*
 * Taken from the "Basic examples" section of:
 * https://en.wikipedia.org/wiki/Standard_deviation
 */
static void test_std_deviation(void)
{
	igt_stats_t stats;
	double mean, variance, std_deviation;

	igt_stats_init(&stats, 8);

	igt_stats_push(&stats, 2);
	igt_stats_push(&stats, 4);
	igt_stats_push(&stats, 4);
	igt_stats_push(&stats, 4);
	igt_stats_push(&stats, 5);
	igt_stats_push(&stats, 5);
	igt_stats_push(&stats, 7);
	igt_stats_push(&stats, 9);

	mean = igt_stats_get_mean(&stats);
	igt_assert(mean == (2 + 3 * 4 + 2 * 5 + 7 + 9) / 8.);

	variance = igt_stats_get_variance(&stats);
	igt_assert(variance == 4);

	std_deviation = igt_stats_get_std_deviation(&stats);
	igt_assert(std_deviation == 2);

	igt_stats_fini(&stats);
}

igt_simple_main
{
	test_mean();
	test_invalidate_mean();
	test_std_deviation();
}