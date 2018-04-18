#ifndef PCG_H
#define PCG_H

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


#include <stdint.h>

// uint64_t state - RNG state. All values are possible.
// uint64_t inc - Controls which RNG sequence (stream) is selected. Must *always* be odd.
typedef struct pcg32_t
{
    uint64_t state;
    uint64_t inc;
} pcg32_t;

uint32_t sys_rand32(void);
uint64_t sys_rand64(void);
uint32_t pcg32_rand(pcg32_t *rng);
void     pcg32_seed(pcg32_t *rng, uint64_t initstate, uint64_t initseq);
float    pcg_rand_unilat(pcg32_t *rng);
float    pcg_rand_bilat(pcg32_t *rng);
void     pcg_seed_global(uint64_t initstate, uint64_t initseq);
float    rand_unilat(void);
float    rand_bilat(void);

#endif
