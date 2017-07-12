type node =
  Js.t {
    .
    name : string,
    id : string,
    isOpen [@bs.set] : Js.null_undefined bool,
    children : Js.null_undefined (array node),
    customComponent : Js.null_undefined ReasonReact.reactClass
  };
