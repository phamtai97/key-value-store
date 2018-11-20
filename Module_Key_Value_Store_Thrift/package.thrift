struct MsgGetRequest{
	1: string key
}

struct MsgSetRequest{
	1: string key,
	2: string value
}

struct MsgRemoveRequest{
	1: string key
}

struct MsgExistRequest{
	1: string key
}

struct MsgGetResponse{
	1: i32 status,
	2: string value
}

struct MsgSetResponse{
	1: i32 status
}

struct MsgRemoveResponse{
	1: bool result
}

struct MsgExistResponse{
	1: bool result
}

service ServiceKeyValueStore{
	MsgGetResponse getApi(1:MsgGetRequest msgGetRequest),
	MsgSetResponse putApi(1:MsgSetRequest msgSetRequest),
	MsgRemoveResponse removeApi(1:MsgRemoveRequest msgRemoveRequest),
	MsgExistResponse existApi(1:MsgExistRequest msgExistRequest)
}
