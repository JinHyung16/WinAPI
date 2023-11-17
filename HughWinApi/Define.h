#pragma once

#define SINGLE(type) public:\
						static type* GetInstance()\
						{ \
							static type ins; \
							return &ins; \
						} \
						private: \
						type(); \
						~type();

#define fDeltaTime CTimeMgr::GetInstance()->GetDeltaTimeF();
#define DeltaTime CTimeMGr::GetInstance()->GetDeltaTime();