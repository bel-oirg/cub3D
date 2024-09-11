/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pk_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmrabe <aelmrabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:03:44 by aelmrabe          #+#    #+#             */
/*   Updated: 2024/06/24 18:07:50 by aelmrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftlib.h"

// void *pk_memmove(void *dst, const void *src, size_t len) 
// {
//     // char buffer[41] = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcde";
//     // char *src = &buffer[2];
//     // char *dst = &buffer[3];
// 	size_t len_in_src;
//     size_t nlen;
//     u_int8_t *csrc;
//     u_int8_t *cdst;

// 	len_in_src = (size_t)(dst - src);
// 	nlen = len % 8;
// 	csrc = (u_int8_t *)src + len;
// 	cdst = (u_int8_t *)dst + len;
//     /*
//       index = 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//         src = 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d e : len = 40
//       index =                               0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 : len = 25
//         dst = - - - - - - - - - - - - - - - x x x x x x x x x x x x x x x x x x x x x x x x x
//    overlap  = - - - - - - - - - - - - - - - 1 2 3 4 5 6 7 8 9 A B C D E 1 2 3 4 5 6 7 8 9 A B 
// memmove src = 1 2 3 4 5 6 7 8 9 A B C D E F 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P : len = 40
// memmove dst = 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P


//       index = 0 1 2 3 4 5 6 7   0 1 2 3 4 5 6 7     0 1 2 3 4 5 6 7     0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//         src = 1 2 3 4 5 6 7 8   9 A B C D E F G     H I J K L M N O     P Q R S T U V W X Y Z a b c d e 
//         dst = - - - - - - - - - - - - - - - x x x x x x x x x x x x x x x x x x x x x x x x x
// memmove dst = 1 2 3 4 5 6 7 8   9 A B C D E F G     H I J K L M N O     P

//     let see my idea check the condition if the src is greater than the dst and the src + len is greater than the dst 
//         if (src < dst && src + len > dst)
//     check diff between dst and src in term of byte that give you number of byte need to move
//     if this case 
//         src = 0x7ff7bfeff2c0
//         dst = 0x7ff7bfeff2cf 
//         src < dst 
//         src + 25 = 
//     */
//     if (dst > src && src + len  >= dst)
//     {
//         len -= nlen;
//         while(nlen-- > 0 || len == 1)
//             *(--cdst) = *(--csrc);
//         while (len > 0)
//         {
//             cdst = cdst - 8;
//             csrc = csrc - 8;
//             pk_memcpy(cdst,csrc,8);
//             len -= 8;
//         }
//     }
//     else 
//         pk_memcpy(dst,src,len);
//     // printf("%s\n",src);
//     // printf("%s\n",dst);
//     return (dst);
// }

// void *pk_memmove(void *dst, void *src, size_t len) 
// {
// 	size_t len_in_src;
//     size_t nlen;
//     u_int8_t *csrc;
//     u_int8_t *cdst;

// 	len_in_src = (size_t)(dst - src);
// 	nlen = len % 8;
// 	csrc = (u_int8_t *)src + len;
// 	cdst = (u_int8_t *)dst + len;
//     if (dst > src && src + len  >= dst)
//     {
//         len -= nlen;
//         while(nlen-- > 0 || len == 1)
//             *(--cdst) = *(--csrc);
//         while (len > 0)
//         {
//             cdst = cdst - 8;
//             csrc = csrc - 8;
//             pk_memcpy(cdst,csrc,8);
//             len -= 8;
//         }
//     }
//     else 
//         pk_memcpy(dst,src,len);
//     return (dst);
// }