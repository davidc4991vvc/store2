// license:BSD-3-Clause
// copyright-holders:Tyler J. Stachecki,Ryan Holtz

<<<<<<< HEAD
rsp_vec_t vec_vrsq(INT32 dp, UINT32 src, UINT32 e, UINT32 dest, UINT32 de)
{
	// Get the element from VT.
	INT16 vt = m_v[src].s[e & 0x7];

	UINT32 dp_input = ((UINT32) m_div_in << 16) | (UINT16) vt;
	UINT32 sp_input = vt;

	INT32 input = (dp) ? dp_input : sp_input;
	INT32 input_mask = input >> 31;
	INT32 data = input ^ input_mask;
=======
rsp_vec_t vec_vrsq(int32_t dp, uint32_t src, uint32_t e, uint32_t dest, uint32_t de)
{
	// Get the element from VT.
	int16_t vt = m_v[src].s[e & 0x7];

	uint32_t dp_input = ((uint32_t) m_div_in << 16) | (uint16_t) vt;
	uint32_t sp_input = vt;

	int32_t input = (dp) ? dp_input : sp_input;
	int32_t input_mask = input >> 31;
	int32_t data = input ^ input_mask;
>>>>>>> upstream/master

	if (input > -32768)
	{
		data -= input_mask;
	}

	// Handle edge cases.
<<<<<<< HEAD
	INT32 result;
=======
	int32_t result;
>>>>>>> upstream/master
	if (data == 0)
	{
		result = 0x7fffffff;
	}
	else if (input == -32768)
	{
		result = 0xffff0000;
	}
	else // Main case: compute the reciprocal.
	{
<<<<<<< HEAD
		UINT32 shift = count_leading_zeros(data);

		UINT32 idx = (((UINT64) data << shift) & 0x7fc00000) >> 22;
=======
		uint32_t shift = count_leading_zeros(data);

		uint32_t idx = (((uint64_t) data << shift) & 0x7fc00000) >> 22;
>>>>>>> upstream/master
		idx = ((idx | 0x200) & 0x3fe) | (shift % 2);
		result = rsp_divtable[idx];

		result = ((0x10000 | result) << 14) >> ((31 - shift) >> 1);
		result = result ^ input_mask;
	}

	// Write out the results.
	m_div_out = result >> 16;
	m_v[dest].s[de & 0x7] = result;

	return vec_load_unshuffled_operand(m_v[dest].s);
}

<<<<<<< HEAD
rsp_vec_t vec_vrsqh(UINT32 src, UINT32 e, UINT32 dest, UINT32 de)
{
	INT16 elements[8];
=======
rsp_vec_t vec_vrsqh(uint32_t src, uint32_t e, uint32_t dest, uint32_t de)
{
	int16_t elements[8];
>>>>>>> upstream/master

	// Get the element from VT.
	memcpy(elements, &m_v[src], sizeof(rsp_vec_t));
	m_div_in = elements[e];

	// Write out the upper part of the result.
	rsp_vec_t vd_mask = _mm_load_si128((rsp_vec_t *) m_vec_helpers.vrsq_mask_table[de]);
	rsp_vec_t vd = _mm_load_si128((rsp_vec_t *) &m_v[dest]);
	vd = _mm_andnot_si128(vd_mask, vd);

	rsp_vec_t b_result = _mm_set1_epi16(m_div_out);
	b_result = _mm_and_si128(vd_mask, b_result);
	return _mm_or_si128(b_result, vd);
}
