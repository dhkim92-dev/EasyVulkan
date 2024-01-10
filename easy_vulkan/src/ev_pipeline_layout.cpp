#ifndef __EV_PIPELINE_LAYOUT_CPP__
#define __EV_PIPELINE_LAYOUT_CPP__

#include "ev_pipeline_layout.h"

using namespace EasyVulkan;

PipelineLayout::PipelineLayout(Device *device) : DeviceBase(device) {

}

PipelineLayout::~PipelineLayout() {
    destroy();
}

VkResult PipelineLayout::create() {
    if(_layout != VK_NULL_HANDLE) {
        LOGE("Already created Pipeline layout.");
        return VK_SUCCESS;
    }

    vector<VkDescriptorSetLayout> ds_layouts;

    for(auto *dsl : _descriptor_set_layouts) {
        ds_layouts.push_back(dsl->layout());
    }

    VkPipelineLayoutCreateInfo info {};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    if(!ds_layouts.empty()) {
        info.pSetLayouts = ds_layouts.data();
        info.setLayoutCount = static_cast<uint32_t>(ds_layouts.size());
    }
    info.pNext = nullptr;

    if(!_constants.empty()) {
        info.pPushConstantRanges = _constants.data();
        info.pushConstantRangeCount = static_cast<uint32_t>(_constants.size());
    }

    return vkCreatePipelineLayout(_device->device(), &info, nullptr, &_layout);
}

void PipelineLayout::set_descriptor_set_layouts(vector<DescriptorSetLayout *> layouts) {
    if(_layout != VK_NULL_HANDLE) {
        LOGE("Can not change descriptor set layouts after VkPipelineLayout created.");
        return;
    }

    if(layouts.empty()) {
        return ;
    }

    _descriptor_set_layouts = layouts;
}

void PipelineLayout::add_constant(VkPushConstantRange range) {
    if(_layout != VK_NULL_HANDLE) {
        LOGE("Can not add push constant after VkPipelineLayout created.");
        return;
    }

    _constants.push_back(range);
}

void PipelineLayout::add_constants(vector<VkPushConstantRange> ranges) {
    if(_layout != VK_NULL_HANDLE) {
        LOGE("Can not add push constants after VkPipelineLayout created.");
        return;
    }

    copy(ranges.begin(), ranges.end(), back_inserter(_constants));
}

VkPipelineLayout PipelineLayout::layout() {
    return _layout;
}

VkPipelineLayout& PipelineLayout::layout_alias() {
    return _layout;
}

VkPipelineLayout* PipelineLayout::layout_ptr() {
    return &_layout;
}

void PipelineLayout::destroy() {
    if(_layout == VK_NULL_HANDLE) {
        return;
    }

    vkDestroyPipelineLayout(_device->device(), _layout, nullptr);
    _layout = VK_NULL_HANDLE;
}

#endif