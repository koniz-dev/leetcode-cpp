%% Definition for singly-linked list.
%%
%% -record(list_node, {val = 0 :: integer(),
%%                     next = null :: 'null' | #list_node{}}).

-spec merge_two_lists(List1 :: #list_node{} | null, List2 :: #list_node{} | null) -> #list_node{} | null.
merge_two_lists(List1, List2) ->
    case {List1, List2} of
        {null, _} -> List2;
        {_, null} -> List1;
        {#list_node{val = V1, next = N1}, #list_node{val = V2, next = N2}} when V1 < V2 ->
            #list_node{val = V1, next = merge_two_lists(N1, List2)};
        {L1, #list_node{val = V2, next = N2}} ->
            #list_node{val = V2, next = merge_two_lists(L1, N2)}
    end.