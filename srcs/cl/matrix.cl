float4	vector_matrix_mul(float4 vector, t_matrix matrix)
{
	return (float4)(
		matrix.s0 * vector.x + matrix.s1 * vector.y + matrix.s2 * vector.z,
		matrix.s4 * vector.x + matrix.s5 * vector.y + matrix.s6 * vector.z,
		matrix.s8 * vector.x + matrix.s9 * vector.y + matrix.sA * vector.z,
		0.0f
	);
}

float4	point_matrix_mul(float4 point, t_matrix matrix)
{
	return (float4)(
		matrix.s0 * point.x + matrix.s1 * point.y + matrix.s2 * point.z + matrix.s3,
		matrix.s4 * point.x + matrix.s5 * point.y + matrix.s6 * point.z + matrix.s7,
		matrix.s8 * point.x + matrix.s9 * point.y + matrix.sA * point.z + matrix.sB,
		0.0f
	);
}
