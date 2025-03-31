/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quaternion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-bouc <bel-bouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:15:32 by bel-bouc          #+#    #+#             */
/*   Updated: 2024/11/25 17:16:25 by senayat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static t_quat	normalizequat(t_quat q)
{
	t_quat	result;
	float	magnitude;

	magnitude = sqrtf(powf(q.x, 2) + powf(q.y, 2)
			+ powf(q.z, 2) + powf(q.w, 2));
	result.x = q.x / magnitude;
	result.y = q.y / magnitude;
	result.z = q.z / magnitude;
	result.w = q.w / magnitude;
	return (result);
}

t_quat	create_quaternion(t_vec cur_vec)
{
	t_quat	q;
	t_vec	des_vec;
	t_vec	temp;

	des_vec.x = 0;
	des_vec.y = 0;
	des_vec.z = -1;
	temp = cross(cur_vec, des_vec);
	q.w = 1 + dot(cur_vec, des_vec);
	q.x = temp.x;
	q.y = temp.y;
	q.z = temp.z;
	q = normalizequat(q);
	return (q);
}

static t_quat	hamilton_product(t_quat q1, t_quat q2)
{
	t_quat	result;

	result.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
	result.x = (q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y);
	result.y = (q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x);
	result.z = (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w);
	return (result);
}

t_vec	rotate_vec(t_vec vec, t_quat q)
{
	t_quat	q_conj;
	t_quat	qv;
	t_quat	qvq;
	t_quat	v;
	t_vec	result;

	v.w = 0;
	v.x = vec.x;
	v.y = vec.y;
	v.z = vec.z;
	q_conj.w = q.w;
	q_conj.x = q.x * -1;
	q_conj.y = q.y * -1;
	q_conj.z = q.z * -1;
	qv = hamilton_product(q, v);
	qvq = hamilton_product (qv, q_conj);
	result.x = qvq.x;
	result.y = qvq.y;
	result.z = qvq.z;
	return (result);
}

t_crd	rotate_crd(t_crd crd, t_quat q)
{
	t_quat	q_conj;
	t_quat	qv;
	t_quat	qvq;
	t_quat	v;
	t_crd	result;

	v.w = 0;
	v.x = crd.x;
	v.y = crd.y;
	v.z = crd.z;
	q_conj.w = q.w;
	q_conj.x = q.x * -1;
	q_conj.y = q.y * -1;
	q_conj.z = q.z * -1;
	qv = hamilton_product(q, v);
	qvq = hamilton_product (qv, q_conj);
	result.x = qvq.x;
	result.y = qvq.y;
	result.z = qvq.z;
	return (result);
}
