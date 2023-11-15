#pragma once

#define SINGLE(type) public:static type* GetInstance() { static type ins; return &ins; }