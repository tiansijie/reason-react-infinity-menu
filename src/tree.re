type node =
  Js.t {
    .
    name : string,
    id : string,
    isOpen : Js.null_undefined bool,
    children : Js.null_undefined (array node)
  };
