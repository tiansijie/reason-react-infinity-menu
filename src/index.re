type tree = array Tree.node;

let component = ReasonReact.statelessComponent "InfinityMenu";

let make tree::(tree: tree) _children => {
  let rec convertTreeToDiv (node: Tree.node) => {
    let id = node##id;
    switch (Js.Null_undefined.to_opt node##children) {
    | Some children =>
      children |>
      Js.Array.reduce
        (
          fun prev (child: Tree.node) => {
            let accu = prev |> Js.Array.concat (convertTreeToDiv child);
            accu
          }
        )
        [||]
    | None => [|<li key=id> (ReasonReact.stringToElement node##name) </li>|]
    }
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
    Js.log results;
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
