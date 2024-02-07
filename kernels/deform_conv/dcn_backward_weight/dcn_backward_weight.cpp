/*************************************************************************
 * Copyright (C) [2024] by Cambricon, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *************************************************************************/
#include <limits.h>
#include <math.h>
#include <vector>

#include "kernels/utils/cnnl_helper.h"

#define DCNBACKWARDWEIGHT_API "mluOpDCNBackwardWeight"

mluOpStatus_t MLUOP_WIN_API mluOpGetDCNBackwardWeightWorkspaceSize(
    mluOpHandle_t handle, const mluOpDCNDescriptor_t dcn_desc,
    const mluOpTensorDescriptor_t input_desc,
    const mluOpTensorDescriptor_t offset_desc,
    const mluOpTensorDescriptor_t mask_desc,
    const mluOpTensorDescriptor_t grad_output_desc,
    const mluOpTensorDescriptor_t grad_filter_desc,
    const mluOpTensorDescriptor_t grad_bias_desc, size_t *size) {
  PARAM_CHECK("mluOpDCNBackwardWeight", handle != NULL);
  PARAM_CHECK("mluOpDCNBackwardWeight", dcn_desc != NULL);
  DEFINE_CREATE_AND_SET_CNNL_HANDLE(handle, _handle);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(input_desc, _input_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(offset_desc, _offset_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(mask_desc, _mask_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(grad_output_desc,
                                               _grad_output_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(grad_filter_desc,
                                               _grad_filter_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(grad_bias_desc, _grad_bias_desc);
  CALL_CNNL(cnnlGetDCNBackwardWeightWorkspaceSize(
      _handle, dcn_desc, _input_desc, _offset_desc, _mask_desc,
      _grad_output_desc, _grad_filter_desc, _grad_bias_desc, size));
  DESTROY_CNNL_TENSOR_DESCRIPTOR(_input_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(_offset_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(_mask_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(_grad_output_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(_grad_filter_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(_grad_bias_desc);
  DESTROY_CNNL_HANDLE(_handle);
  return MLUOP_STATUS_SUCCESS;
}

mluOpStatus_t MLUOP_WIN_API mluOpDCNBackwardWeight(
    mluOpHandle_t handle, const mluOpDCNDescriptor_t dcn_desc,
    const mluOpTensorDescriptor_t input_desc, const void *input,
    const mluOpTensorDescriptor_t offset_desc, const void *offset,
    const mluOpTensorDescriptor_t mask_desc, const void *mask,
    const mluOpTensorDescriptor_t grad_output_desc, const void *grad_output,
    void *workspace, const size_t workspace_size,
    const mluOpTensorDescriptor_t grad_filter_desc, void *grad_filter,
    const mluOpTensorDescriptor_t grad_bias_desc, void *grad_bias) {
  PARAM_CHECK(DCNBACKWARDWEIGHT_API, handle != NULL);
  if (workspace_size > 0) {
    PARAM_CHECK(DCNBACKWARDWEIGHT_API, workspace != NULL);
  }
  DEFINE_CREATE_AND_SET_CNNL_HANDLE(handle, cnnl_handle);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(input_desc, cnnl_input_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(offset_desc, cnnl_offset_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(mask_desc, cnnl_mask_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(grad_output_desc,
                                               cnnl_grad_output_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(grad_filter_desc,
                                               cnnl_grad_filter_desc);
  DEFINE_CREATE_AND_SET_CNNL_TENSOR_DESCRIPTOR(grad_bias_desc,
                                               cnnl_grad_bias_desc);
  CALL_CNNL(cnnlDCNBackwardWeight(
      cnnl_handle, dcn_desc, cnnl_input_desc, input, cnnl_offset_desc, offset,
      cnnl_mask_desc, mask, cnnl_grad_output_desc, grad_output, workspace,
      workspace_size, cnnl_grad_filter_desc, grad_filter, cnnl_grad_bias_desc,
      grad_bias));
  DESTROY_CNNL_TENSOR_DESCRIPTOR(cnnl_input_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(cnnl_offset_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(cnnl_mask_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(cnnl_grad_output_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(cnnl_grad_filter_desc);
  DESTROY_CNNL_TENSOR_DESCRIPTOR(cnnl_grad_bias_desc);
  DESTROY_CNNL_HANDLE(cnnl_handle);
  return MLUOP_STATUS_SUCCESS;
}
