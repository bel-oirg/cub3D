// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pk_memset.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/14 14:03:17 by aelmrabe          #+#    #+#             */
// /*   Updated: 2024/05/15 03:46:24 by aelmrabe         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/ftlib.h"

// void pk_memset_pattern_64(void *dst, void *src, int len)
// {
// 	uint64_t *chunks_s;
// 	uint64_t *chunks_d;

// 	chunks_s = (uint64_t*)src;
// 	chunks_d = (uint64_t*)dst;
// 	while(len--)
// 	{
// 		*(chunks_d) = *(chunks_s);
// 		chunks_d++;
// 		chunks_s++;
// 	}
// }

// void pk_memset_pattern_32(void *dst, void *src, int len)
// {
// 	const uint32_t *chunks_s;
// 	uint32_t *chunks_d;

// 	chunks_s = (uint32_t*)src;
// 	chunks_d = (uint32_t*)dst;
// 	while(len--)
// 	{
// 		*(chunks_d) = *(chunks_s);
// 		chunks_d++;
// 		chunks_s++;
// 	}
// }

// void pk_memset_pattern_16(void *dst, void *src, int len)
// {
// 	const uint16_t *chunks_s;
// 	uint16_t *chunks_d;

// 	chunks_s = (uint16_t*)src;
// 	chunks_d = (uint16_t*)dst;
// 	while(len--)
// 	{
// 		*(chunks_d) = *(chunks_s);
// 		chunks_d++;
// 		chunks_s++;
// 	}
// }

// void pk_memset_pattern_8(void *dst, void *src, int len)
// {
// 	const uint8_t *chunks_s;
// 	uint8_t *chunks_d;

// 	chunks_s = (uint8_t*)src;
// 	chunks_d = (uint8_t*)dst;
// 	while(len--)
// 	{
// 		*(chunks_d) = *(chunks_s);
// 		chunks_d++;
// 		chunks_s++;
// 	}
// }

// void *pk_memset(void *dst, int c, int len)
// {
// 	uint8_t *chunks_d;

// 	chunks_d = (uint8_t*)dst;
// 	while(len--)
// 		*(chunks_d++) = (uint8_t)(c);
// 	return (dst);
// }
