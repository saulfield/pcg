/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For additional information about the PCG random number generation scheme,
 * including its license and other licensing options, visit
 *
 *     http://www.pcg-random.org
 */


// TODO: Add other platforms, explicitly check for glibc versions, etc.
#define LINUX

#ifdef LINUX
#define _GNU_SOURCE
#include <stdint.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/random.h>

#include "pcg.h"

// platform-specific RNG
uint32_t sys_rand32(void)
{
    uint32_t result;
    syscall(SYS_getrandom, &result, 4, 0);
    return result;
}

uint64_t sys_rand64(void)
{
    uint64_t result;
    syscall(SYS_getrandom, &result, 8, 0);
    return result;
}
#else
#error A valid platform was not defined.
#endif

// Generate a uniformly distributed 32-bit random number
uint32_t pcg32_rand(pcg32_t *rng)
{
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

// Seed the rng.  Specified in two parts, state initializer and a
// sequence selection constant (a.k.a. stream id)
void pcg32_seed(pcg32_t *rng, uint64_t initstate, uint64_t initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_rand(rng);
    rng->state += initstate;
    pcg32_rand(rng);
}

// returns result in [0, 1]
float pcg_rand_unilat(pcg32_t *rng)
{
    float result = (float)pcg32_rand(rng) / UINT32_MAX;
    return result;
}

// returns result in [-1, 1]
float pcg_rand_bilat(pcg32_t *rng)
{
    float result = 2.0f * pcg_rand_unilat(rng) - 1.0f;
    return result;
}

// Static RNG for convenience
static pcg32_t global_rng;

void pcg_seed_global(uint64_t initstate, uint64_t initseq)
{
    pcg32_seed(&global_rng, initstate, initseq);
}

// returns result in [0, 1]
float rand_unilat(void)
{
    float result = (float)pcg32_rand(&global_rng) / UINT32_MAX;
    return result;
}

// returns result in [-1, 1]
float rand_bilat(void)
{
    float result = 2.0f * pcg_rand_unilat(&global_rng) - 1.0f;
    return result;
}
