isValid(S) ->
    isValid(S, []).

isValid([], []) -> true;
isValid([], _) -> false;
isValid([C|T], Stack) when C =:= $({; C =:= $[; C =:= ${ ->
    isValid(T, [C|Stack]);
isValid([C|T], [H|Stack]) ->
    case {C, H} of
        ($), $() -> isValid(T, Stack);
        ($], $[) -> isValid(T, Stack);
        ($}, ${) -> isValid(T, Stack);
        _ -> false
    end;
isValid(_, _) -> false.
