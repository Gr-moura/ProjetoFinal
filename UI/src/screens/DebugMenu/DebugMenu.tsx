import { useState } from 'react'
import "./DebugMenu.css"
import { SingleLevelDropdownMenu } from '../../components/dropdown/dropdown';
import { Link } from 'react-router-dom';

export const DebugMenu = ()=>{
  const [selected_width, setWidht] = useState(0);
  const [selected_height, setHeight] = useState(0);
  const [selected_players, setPlayerNumber] = useState(2);

  const xlist = []
  const ylist = []
  for(let i=1; i<13; i++){
    xlist.push({
      title:i.toString(),
      action:()=>setWidht(i)
    })
    ylist.push({
      title:i.toString(),
      action:()=>setHeight(i)
    })
  }
  const playerlist = []
  for(let i=2; i<5; i++){
    playerlist.push({
        title:i.toString(),
        action:()=>setPlayerNumber(i),
    })
  }

  return (
    <div className='menubody'>
      <div style={{marginTop:100}}>
        <div className='dimensioninput'>
          <a style={{marginRight:10, color:'white'}}>board dimensions: </a>
          <SingleLevelDropdownMenu buttonLabel='widht' items={xlist}></SingleLevelDropdownMenu>
          <a style={{color:"white"}}>X</a>
          <SingleLevelDropdownMenu buttonLabel='height' items={ylist}></SingleLevelDropdownMenu>
        </div>
        <div className='dimensioninput'>
          <a style={{marginRight:10, color:'white'}}>player number: </a>
          <SingleLevelDropdownMenu buttonLabel='players' items={playerlist}></SingleLevelDropdownMenu>
        </div>
      </div>
      <Link to={"/board"} state={{widht:selected_width, height:selected_height}}>
        <button className='startbutton'>start</button>
      </Link>
    </div>
  )
}