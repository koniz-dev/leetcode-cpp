-spec two_sum([integer()], integer()) -> [integer()].
two_sum(Nums, Target) ->
    two_sum_helper(Nums, Target, 0, #{}, []).

two_sum_helper([], _, _, _, _) ->
    []; % Base case: Empty list, no solution found
two_sum_helper([Num | Rest], Target, Index, Seen, Result) ->
    Complement = Target - Num,
    case maps:is_key(Complement, Seen) of
        true ->
            [maps:get(Complement, Seen), Index];
        false ->
            NewSeen = maps:put(Num, Index, Seen),
            two_sum_helper(Rest, Target, Index + 1, NewSeen, Result)
    end.
