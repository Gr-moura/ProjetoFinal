import "./Menu.css";
import { MenuBanner } from "../../components/MenuBanner/MenuBanner"
import jogodavelhaImage from "../../assets/jogodavelha.jpg"
import connectfourImage from "../../assets/connectfour.jpg"
import reversiImage from "../../assets/reversi.jpg"
import { useEffect, useState } from "react";
import { useLocation, useNavigate } from "react-router-dom";
import { Selector } from "../../components/Selector/Selector";
import { playerType } from "../PlayerSelection/PlayerSelection";


/**
 * @interface MenuProps
 * @brief Propriedades do menu.
 * @property {playerType} player1 Informações do jogador 1.
 * @property {playerType} player2 Informações do jogador 2.
 */
interface MenuProps{
    player1:playerType;
    player2:playerType;
}


/**
 * @brief Componente principal do menu.
 * @return {JSX.Element} Retorna o componente do menu.
 */
export const Menu = () => {
    const navigate = useNavigate();
    const location = useLocation();
    const {player1, player2}:MenuProps = location.state;

    const dificultieSettings = [
        {name:"fácil", value:0, index:0},
        {name:"médio", value:3, index:1},
        {name:"difícil", value:9, index:2}
    ]
    const boardsizeSettings = [
        {name:"3", value:3, index:0},
        {name:"4", value:4, index:1},
        {name:"5", value:5, index:2},
        {name:"6", value:6, index:3},
        {name:"7", value:7, index:4},
        {name:"8", value:8, index:5},
        {name:"9", value:9, index:6},
        {name:"10", value:10, index:7},
    ]

    const [selectedHeight, setSelectedHeight] = useState<number>(boardsizeSettings[0].value);
    const [selectedWidht, setSelectedWidht] = useState<number>(boardsizeSettings[0].value);
    const [selectedDificulty, setSelectedDificulty] = useState<number>(dificultieSettings[0].value);

    const [highlitActive, setHighlightActive] = useState<boolean>(player2.playerName=="AI");
    const [highlitedItems, setHighlitedItems] = useState<boolean[]>([player2.playerName=="AI", false, false]);

    /**
     * @brief Destaca um item do menu.
     * @param {number} id Índice do item a ser destacado.
     */
    const highlightItem = (id:number)=> {
        let updatedArray = [...highlitedItems];
        //@ts-ignore
        updatedArray.forEach((item, index)=>{
            if(index===id) updatedArray[index] = true;
            else updatedArray[index] = false;
        });
        setHighlitedItems(updatedArray);
        setHighlightActive(true);
    }

    /**
     * @brief Remove o destaque de todos os itens do menu.
     */
    const unhighlightAll = () => {
        let updatedArray = [...highlitedItems];
        updatedArray.forEach((item, index)=>{
            if(item) updatedArray[index] = false;
        })
        setHighlitedItems(updatedArray);
        setHighlightActive(false);
    }
    
    /**
     * @brief Ação ao clicar em um banner do menu.
     * @param {number} id Índice do banner clicado.
     * @param {string} gameName Nome do jogo associado ao banner.
     */
    const bannerAction = (id:number, gameName:string) => {
        if(highlitedItems[id]){
            console.log(selectedDificulty, selectedHeight, selectedWidht);
            navigate("/board", {state:{
                height:selectedHeight, 
                widht:selectedWidht, 
                dificulty:selectedDificulty, 
                gameName:gameName, 
                playernames:[player1.playerNick, player2.playerNick]
            }});
        }
        else{
            console.log("highlighted", id);
            highlightItem(id);
        }
    }

    /**
     * @brief Ajusta o tamanho do tabuleiro com base no jogo selecionado.
     */
    useEffect(()=>{
        if(highlitedItems[0]){
            setSelectedHeight(3);
            setSelectedWidht(3);
        }
        if(highlitedItems[1]){
            setSelectedHeight(6);
            setSelectedWidht(7);
        }
        if(highlitedItems[2]){
            setSelectedHeight(8);
            setSelectedWidht(8);
        }
    }, [highlitedItems]);

    return (
        <div className="menubody">
            <MenuBanner 
                className={highlitActive?(highlitedItems[0]?"highlighted":"hide"):("")}
                gameName="Jogo da Velha"
                gameDescription='O jogo da velha é um jogo simples em um tabuleiro 3x3, 
                    onde dois jogadores alternam-se marcando as casas para formar uma linha de três. 
                    Originado na Antiguidade, com registros no Egito e Roma, 
                    permanece popular por sua simplicidade e desafio estratégico.'
                gameImage={jogodavelhaImage}
                id={0}
                action={bannerAction}
            />
            <MenuBanner
                className={highlitActive?(highlitedItems[1]?"highlighted":"hide"):("")}
                gameName="Ligue Quatro"
                gameDescription="Ligue Quatro é um jogo onde dois jogadores alternam colocando discos em uma grade de 6x7, 
                    tentando formar uma linha de quatro. Criado em 1974, é popular por sua simplicidade e estratégia."
                gameImage={connectfourImage}
                id={1}
                action={bannerAction}
            />
            <MenuBanner
                className={highlitActive?(highlitedItems[2]?"highlighted":"hide"):("")}
                gameName="Reversi"
                gameDescription="Reversi é um jogo de tabuleiro para dois jogadores, 
                    onde o objetivo é conquistar o maior número de peças do adversário, 
                    virando-as para a cor própria ao cercá-las com peças próprias. 
                    O jogo é jogado em um tabuleiro de 8x8, com peças de dois lados, preto e branco. 
                    Criado no século XIX por Lewis Waterman, 
                    foi popularizado com o nome Othello na década de 1970 e continua sendo um desafio estratégico até hoje."
                gameImage={reversiImage}
                id={2}
                action={bannerAction}
            />
            {highlitActive && (
                <div style={{marginTop:"22px", marginLeft:"-50px"}}>
                    <div>
                        <a className="selectortitle">Jogadores:</a>
                        <div style={{display:"flex", flexDirection:"row", alignItems:"center"}}>
                            <a className="menuplayername">{player1.playerNick}</a>
                            <a style={{marginRight:"5px", marginLeft:"5px"}}> vs </a>
                            <a className="menuplayername">{player2.playerNick}</a>
                        </div>
                    </div>
                    {player2.playerNick==="AI" && (<div>
                        <a className="selectortitle">Selecione a dificuldade:</a>
                        <Selector items={dificultieSettings} setAction={setSelectedDificulty}/>
                    </div>)}
                    {/*<div>
                        <a className="selectortitle">Selecione o tamanho do tabuleiro:</a>
                        <div style={{display:"flex", flexDirection:"row", alignItems:"center"}}>
                            <Selector items={boardsizeSettings} setAction={setSelectedWidht}/>
                            <a style={{marginRight:"5px", marginLeft:"5px"}}> por </a>
                            <Selector items={boardsizeSettings} setAction={setSelectedHeight}/>
                        </div>
                    </div>*/}
                </div>
            )}
            {highlitActive && player2.playerName!="AI" && (
                <div className="highlightdiv" onClick={() => unhighlightAll()}/>
            )}
        </div>
    )
}