type tree = array Tree.node;

let component = ReasonReact.statelessComponent "InfinityMenu";

let make tree::(tree: tree) _children => {
  let rec convertTreeToDiv (node: Tree.node) => {
    Js.log node;
    let id = node##id;
    let arr = [||];
    switch node##children {
    | Some children => Js.log children
    | None => ()
    };
    /* switch node##children {
       | Some children =>
         Array.map (fun child => Js.log child) children;
         [||]
       /* children |>
          Js.Array.reduce
            (
              fun accu (child: Tree.node) => {
                Js.log child;
                accu |> Array.append (convertTreeToDiv child)
              }
            )
            arr */
       | None =>
         arr |>
         Array.append [|
           <li key=id> (ReasonReact.stringToElement node##name) </li>
         |]
       }; */
    arr
  };
  let convertTree (tree: tree) => {
    let results =
      tree |>
      Array.fold_left
        (
          fun accu (node: Tree.node) =>
            accu |> Array.append (convertTreeToDiv node)
        )
        [||];
    ReasonReact.arrayToElement results
  };
  {
    ...component,
    render: fun _self => {
      let displayTree = convertTree tree;
      <div> displayTree </div>
    }
  }
};

let jsComponent =
  ReasonReact.wrapReasonForJs
    ::component (fun jsProps => make tree::jsProps##tree [||]);
