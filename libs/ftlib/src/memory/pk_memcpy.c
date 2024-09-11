// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pk_memcpy.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/14 13:59:33 by aelmrabe          #+#    #+#             */
// /*   Updated: 2024/05/24 15:56:21 by aelmrabe         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/ftlib.h"

// void pk_memcpy_patterns(void *dst, void *src, int *len)
// {
//     while (*len >= 8)
//     {
//         pk_memset_pattern_64(dst, src, 1);
//         dst += 8;
//         src += 8;
//         *len -= 8;
//     }
//     while (*len >= 4)
//     {
//         pk_memset_pattern_32(dst, src, 1);
//         dst += 4;
//         src += 4;
//         *len -= 4;
//     }
//     // while (*len >= 2)
//     // {
//     //     pk_memset_pattern_16(dst, src, 1);
//     //     dst += 2;
//     //     src += 2;
//     //     *len -= 2;
//     // }
//     while (*len <= 3 && *len > 0)
//     {
//         pk_memset_pattern_8(dst,src,1);
//         dst += 1;
//         src += 1;
//         *len -= 1;
//     }
// }

// void pk_memccpy_patterns(void *dst, void *src, int *len)
// {
//     while (*len >= 8)
//     {
//         pk_memset_pattern_64(dst, src, 1);
//         *((uint64_t *)src) = 0;
//         dst += 8;
//         src += 8;
//         *len -= 8;
//     }
//     while (*len >= 4)
//     {
//         pk_memset_pattern_32(dst, src, 1);
//         *((uint32_t *)src) = 0;
//         dst += 4;
//         src += 4;
//         *len -= 4;
//     }
//     while (*len <= 3 && *len > 0)
//     {
//         pk_memset_pattern_8(dst, src, 1);
//         *((uint8_t *)src) = 0;
//         dst += 1;
//         src += 1;
//         *len -= 1;
//     }
// }

// /*
// 	the idea of this function i was thinking about it 
// 	for a while but i see this article and i was like
// 	https://medium.com/@caruychen_48871/the-curious-case-of-memcpy-bd93936e5136
// 	so i decided to implement using my own method 
// 	it and it's working fine i will try to optimize gnl 
// 	using this Method and see if it's working fine
// */
// void *pk_memcpy(void *dst, void *src, int len)
// {
//     void *csrc;
//     void *cdst;

//     cdst = dst;
//     csrc = src;
//     while (len > 0)
//         pk_memcpy_patterns(cdst,csrc,&len);
//     return (dst);
// }

// void *pk_memccpy(void *dst, void *src, int len)
// {
//     void *csrc;
//     void *cdst;

//     cdst = dst;
//     csrc = src;
//     if (dst == src || len == 0)
//         return (dst);
//     while (len > 0)
//         pk_memccpy_patterns(cdst,csrc,&len);
//     return (dst);
// }

